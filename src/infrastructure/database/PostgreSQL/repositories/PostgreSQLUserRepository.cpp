#include <iostream>
#include <utility>

#include "infrastructure/database/PostgreSQL/repositories/PostgreSQLUserRepository.h"

#include "domain/UserStats.h"
#include "domain/sudoku/enums/SudokuGameStatus.h"
#include "infrastructure/database/PostgreSQL/PostgreSQLQuery.h"

#define START_RATING 1000

PostgreSQLUserRepository::PostgreSQLUserRepository(std::shared_ptr<PostgreSQLDatabase> database) {
    this->database = std::move(database);
}

std::optional<User> PostgreSQLUserRepository::create(
    User newUser
) {
    if (!database->isConnected()) {
        return std::nullopt;
    }

    try {
        PostgreSQLQuery query(std::format(R"(
            WITH inserted_user AS (
                INSERT INTO users (username, email, password_hash)
                VALUES ($1, $2, $3)
                RETURNING id, created_at
            ),
            inserted_rating AS (
                INSERT INTO rating_history (user_id, rating_change, new_rating, comment)
                SELECT
                    id,
                    {} AS rating_change,
                    {} AS new_rating,
                    'Start rating after registration' AS comment
                FROM inserted_user
                RETURNING user_id, rating_change, new_rating, comment
            )
            SELECT id, created_at
            FROM inserted_user;
        )", START_RATING, START_RATING));
        query.addParameter(newUser.getUsername());
        query.addParameter(newUser.getEmail());
        query.addParameter(newUser.getPasswordHash());

        const pqxx::result result = database->execute(query);
        if (result.empty()) {
            throw std::runtime_error("Failed to create user");
        }
        const pqxx::row row = result[0];
        int id = row["id"].as<int>();
        auto createdAt = row["created_at"].as<std::string>();
        return User(
            id,
            newUser.getUsername(),
            newUser.getEmail(),
            newUser.getPasswordHash(),
            1000,
            createdAt,
            false
        );

    } catch (const std::exception &e) {
        std::cout << "PostgreSQLUserRepository::create(): " << e.what() << std::endl;
        return std::nullopt;
    }
}

std::string PostgreSQLUserRepository::getHashedPassword(const std::string &username) const {
    if (!database->isConnected()) {
        throw std::runtime_error("Database is not connected");
    }
    PostgreSQLQuery query("SELECT password_hash FROM users WHERE username = $1");
    query.addParameter(username);

    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        return {};
    }

    const pqxx::row row = result[0];

    return row["password_hash"].as<std::string>();
}

std::optional<User> PostgreSQLUserRepository::get(int id) {
    if (!database->isConnected()) {
        return std::nullopt;
    }

    PostgreSQLQuery query(R"(
        SELECT
            u.id,
            u.username,
            u.email,
            u.password_hash,
            u.created_at,
            rh.new_rating AS rating
        FROM
            users u
        LEFT JOIN (
            SELECT
                user_id,
                new_rating
            FROM
                rating_history
            WHERE
                (user_id, timestamp) IN (
                    SELECT
                        user_id,
                        MAX(timestamp)
                    FROM
                        rating_history
                    GROUP BY
                        user_id
                )
        ) rh ON u.id = rh.user_id
        WHERE
            u.id = $1;
    )");

    query.addParameter(std::to_string(id));

    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        return std::nullopt;
    }

    const pqxx::row row = result[0];

    int finalId = row["id"].as<int>();
    const auto finalUsername = row["username"].as<std::string>();
    const auto email = row["email"].as<std::string>();
    const auto finalPasswordHash = row["password_hash"].as<std::string>();
    const auto createdAt = row["created_at"].as<std::string>();
    const std::optional<int> rating = row["rating"].is_null()
                                          ? std::nullopt
                                          : std::make_optional(row["rating"].as<int>());

    return User(finalId, finalUsername, email, finalPasswordHash, rating, createdAt, false);
}


std::optional<User> PostgreSQLUserRepository::get(const std::string &username) {
    if (!database->isConnected()) {
        return std::nullopt;
    }

    PostgreSQLQuery query(R"(
        SELECT
            u.id,
            u.username,
            u.email,
            u.password_hash,
            u.created_at,
            rh.new_rating AS rating
        FROM
            users u
        LEFT JOIN (
            SELECT
                user_id,
                new_rating
            FROM
                rating_history
            WHERE
                (user_id, timestamp) IN (
                    SELECT
                        user_id,
                        MAX(timestamp)
                    FROM
                        rating_history
                    GROUP BY
                        user_id
                )
        ) rh ON u.id = rh.user_id
        WHERE
            u.username = $1;
    )");
    query.addParameter(username);

    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        return std::nullopt;
    }

    const pqxx::row row = result[0];

    int id = row["id"].as<int>();
    const auto finalUsername = row["username"].as<std::string>();
    const auto email = row["email"].as<std::string>();
    const auto finalPasswordHash = row["password_hash"].as<std::string>();
    const auto createdAt = row["created_at"].as<std::string>();
    const std::optional<int> rating = row["rating"].is_null()
                                          ? std::nullopt
                                          : std::make_optional(row["rating"].as<int>());

    return User(id, finalUsername, email, finalPasswordHash, rating, createdAt, false);
}

bool PostgreSQLUserRepository::isUsernameTaken(const std::string &username) const {
    if (!database->isConnected()) {
        return false;
    }
    PostgreSQLQuery query("SELECT COUNT(*) FROM users WHERE username = $1");
    query.addParameter(username);
    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        return false;
    }
    const pqxx::row row = result[0];
    return row[0].as<int>() > 0;
}

bool PostgreSQLUserRepository::isEmailTaken(const std::string &email) const {
    if (!database->isConnected()) {
        return false;
    }
    PostgreSQLQuery query("SELECT COUNT(*) FROM users WHERE email = $1");
    query.addParameter(email);
    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        return false;
    }
    const pqxx::row row = result[0];
    return row[0].as<int>() > 0;
}

UserStats PostgreSQLUserRepository::getUserStats(const int userId) const {
    if (!database->isConnected()) {
        return UserStats();
    }

    PostgreSQLQuery query(R"(
        WITH game_stats AS (
            SELECT
                user_id,
                COUNT(*) AS total_games,
                COUNT(*) FILTER (WHERE status = $1) AS finished_games,
                ROUND(AVG(EXTRACT(EPOCH FROM end_time - start_time)))::int AS avg_solution_time_seconds
            FROM games
            WHERE end_time IS NOT NULL AND user_id = $2
            GROUP BY user_id
        ),
        most_common_difficulty AS (
            SELECT user_id, difficulty
            FROM (
                SELECT
                    user_id,
                    difficulty,
                    COUNT(*) AS games_played,
                    ROW_NUMBER() OVER (PARTITION BY user_id ORDER BY COUNT(*) DESC) AS rn
                FROM games
                WHERE user_id = $2
                GROUP BY user_id, difficulty
            ) sub
            WHERE rn = 1
        )
        SELECT
            gs.user_id,
            gs.total_games,
            gs.finished_games,
            gs.avg_solution_time_seconds,
            mcd.difficulty AS most_common_difficulty
        FROM game_stats gs
        LEFT JOIN most_common_difficulty mcd ON gs.user_id = mcd.user_id;
    )");
    query.addParameter(SudokuGameStatus::toString(SudokuGameStatusEnum::FINISHED));
    query.addParameter(std::to_string(userId));

    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        return UserStats();
    }

    const pqxx::row row = result[0];
    const int totalGames = row["total_games"].as<int>();
    const int finishedGames = row["finished_games"].as<int>();
    const int avgSolutionTime = row["avg_solution_time_seconds"].is_null()
                                    ? 0
                                    : row["avg_solution_time_seconds"].as<int>();
    const std::string mostCommonDifficulty = row["most_common_difficulty"].is_null()
                                            ? ""
                                            : row["most_common_difficulty"].as<std::string>();

    return UserStats(
        totalGames,
        finishedGames,
        avgSolutionTime,
        SudokuDifficulty::fromString(mostCommonDifficulty)
    );
}


