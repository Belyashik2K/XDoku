![XDoku](https://github.com/user-attachments/assets/d518d11b-226d-4894-91d4-7a4994dac2ef)

# XDoku 🎮

**A cross-platform Sudoku desktop app with accounts, a leaderboard, and progress tracking.**

> Design board: https://miro.com/app/board/uXjVI8V73Is=

## About

XDoku is a Sudoku implementation built as a coursework project, focused on:

- **Interactivity** — a native ImGui interface with immediate visual feedback.
- **Accounts & competition** — sign up, sign in, and a global leaderboard.
- **Progress tracking** — stats on solved puzzles, average time, and difficulty.

## Features ✨

- **Accounts & profile** — create an account to track your achievements.
- **Leaderboard** — compete against other players' ratings.
- **Statistics** — puzzles solved, average time, difficulty breakdown.
- **Autosave** — the current game is saved automatically on exit.
- **Difficulty levels** — Easy, Medium, Hard, Expert.

## Tech stack 🛠️

- **Language**: C++20, OOP-focused.
- **Rendering**: OpenGL via GLFW + GLAD + Dear ImGui.
- **Persistence**: PostgreSQL through `libpqxx`.
- **Schema migrations**: Alembic (Python).
- **Password hashing**: [`bcrypt`](https://github.com/trusch/libbcrypt), vendored under `deps/bcrypt`.
- **Architecture**: MVP (Model-View-Presenter), with the database layer fully abstracted behind
  `IDatabase` / `IRepositoryFactory` interfaces (see `include/interfaces/database`).

## Project status 🚧

This project is **archived and no longer under active development**. It's published as-is for
reference. Issues and PRs may not be reviewed.

## Platform support

The rendering stack (GLFW/OpenGL/ImGui) and the database layer are portable, and the code has been
audited to remove the Linux-only assumptions the project originally had (it was developed and
tested on Kali Linux).

| Platform | Status | Notes |
|---|---|---|
| Linux | ✅ Yes | Originally developed and tested here. |
| macOS | ✅ Yes | Built, ran, and connected to a local Postgres end to end on Apple Silicon. |
| Windows | ⚠️ Should work | Needs vcpkg/MSYS2 packages below; not build-tested by the maintainer. `pthread` linkage may need MSVC-specific handling. |

## Getting started

### 1. Prerequisites

You need a C++20 compiler, CMake 3.30+, and the following libraries: **GLFW3**, **OpenGL**,
**PostgreSQL** and **libpqxx**. (`bcrypt` is vendored in `deps/bcrypt` — nothing to install for it.)

<details>
<summary>Linux (Debian/Ubuntu/Kali)</summary>

```bash
sudo apt install build-essential cmake libglfw3-dev libgl1-mesa-dev libpq-dev libpqxx-dev postgresql
```
</details>

<details>
<summary>macOS (Homebrew)</summary>

```bash
brew install cmake glfw libpqxx postgresql@16
```
</details>

<details>
<summary>Windows (vcpkg)</summary>

```powershell
vcpkg install glfw3 libpqxx
```

Use the vcpkg CMake toolchain file when configuring the project
(`-DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>/scripts/buildsystems/vcpkg.cmake`).
</details>

### 2. Configure environment

```bash
cp .env.example .env
```

`.env` holds the DB connection settings (`XDOKU_DB_USER`, `XDOKU_DB_PASSWORD`, `XDOKU_DB_HOST`,
`XDOKU_DB_PORT`, `XDOKU_DB_NAME`). It's read by `docker-compose.yml`, by the app itself (loaded at
startup, see `EnvConfig`), and by the Alembic migrations — so all three always agree on where the
database is. The defaults in `.env.example` work out of the box with the Docker setup below; change
them only if you're pointing at your own PostgreSQL instance.

### 3. Database

The easiest way to get a local PostgreSQL instance is Docker:

```bash
docker compose up -d
```

This starts Postgres on `localhost:5432` using the credentials from `.env`. No further setup
needed for a fresh run.

### 4. Run migrations

Schema migrations are managed with Alembic, and Alembic needs to be run from the directory
containing `alembic.ini`:

```bash
cd src/infrastructure/database/PostgreSQL/migrations
python3 -m venv .venv
source .venv/bin/activate   # on Windows: .venv\Scripts\activate
pip install alembic sqlalchemy psycopg2-binary python-dotenv
alembic upgrade head
```

(`.venv` is already covered by `.gitignore`.)

### 5. Build

```bash
cmake -B build -S .
cmake --build build
```

### 6. Run

The app loads assets via relative paths (`../assets/...`), so run it from one directory below the
project root — e.g. straight out of the `build` directory:

```bash
cd build
./XDoku
```

## License

- **Code** is licensed under the [MIT License](LICENSE-CODE.txt).
- **Content** (art, textures, sounds) is licensed under
  [CC BY-NC 4.0](LICENSE-CONTENT.txt).
