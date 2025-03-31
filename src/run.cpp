#include <iostream>
#include <pqxx/pqxx>

#include "../include/models/PostgreSQLDatabase.h"

int main() {
    try {
        const std::string connectionString = "";
        PostgreSQLDatabase database(connectionString);
        database.connect();
        std::cout << "Connected to database!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
