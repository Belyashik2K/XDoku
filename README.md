<p align="center">
  <img src="https://github.com/user-attachments/assets/d518d11b-226d-4894-91d4-7a4994dac2ef" alt="XDoku" />
</p>

<h1 align="center">XDoku</h1>

<p align="center"><strong>A cross-platform Sudoku desktop app with accounts, a leaderboard, and progress tracking.</strong></p>

<p align="center"><a href="https://miro.com/app/board/uXjVI8V73Is=">Design board</a></p>

## About

XDoku is a Sudoku implementation built as a coursework project: a native ImGui interface, accounts
with a global leaderboard, and per-game progress tracking.

## Features

- **Accounts & profile** — sign up, sign in, track your achievements.
- **Leaderboard** — compete against other players' ratings.
- **Statistics** — puzzles solved, average time, difficulty breakdown.
- **Autosave** — the current game is saved automatically on exit.
- **Difficulty levels** — Easy, Medium, Hard, Expert.

## Tech stack

- **Language**: C++20.
- **Rendering**: OpenGL via GLFW + GLAD + Dear ImGui.
- **Persistence**: PostgreSQL through `libpqxx`.
- **Migrations**: Alembic.
- **Password hashing**: [bcrypt](https://github.com/trusch/libbcrypt), vendored in `deps/bcrypt`.
- **Architecture**: MVP, with the DB layer abstracted behind `IDatabase`/`IRepositoryFactory` (see
  `include/interfaces/database`).

## Project status

This project is **archived and no longer under active development**. Published as-is for
reference; issues and PRs may not be reviewed.

## Platform support

| Platform | Status | Notes |
|---|---|---|
| Linux | Yes | Developed on Kali; also verified on Ubuntu 26.04 (`libpqxx-dev` 7.10.0-2build1, `libpq-dev` 18.6-0ubuntu0.26.04.1). |
| macOS | Yes | Verified on Apple Silicon. |
| Windows | Yes | Verified with MSVC + vcpkg + CMake/Ninja — see [Windows](#windows) below. |

## Getting started

### macOS / Linux

**1. Prerequisites** — a C++20 compiler, CMake 3.30+, GLFW3, OpenGL, PostgreSQL client headers,
and libpqxx (`bcrypt` is vendored, nothing to install for it).

<details>
<summary>Linux (Debian/Ubuntu/Kali)</summary>

```bash
sudo apt install build-essential cmake libglfw3-dev libgl1-mesa-dev libpq-dev libpqxx-dev
```

This installs only the Postgres *client* headers — the database runs via Docker (step 3). Don't
also install the `postgresql` server package: apt auto-starts it via systemd, and it'll squat on
port 5432 before Docker's Postgres container gets a chance to bind it.
</details>

<details>
<summary>macOS (Homebrew)</summary>

```bash
brew install cmake glfw libpqxx postgresql@16
```
</details>

**2. Configure environment**

```bash
cp .env.example .env
```

Holds the DB connection settings, shared by Docker, the app, and Alembic — see
[`.env.example`](.env.example).

**3. Database**

```bash
docker compose up -d
```

Starts Postgres and applies migrations automatically (see [Migrations](#migrations)).

> Port 5432 already in use? Something else already has a Postgres bound to it — stop that one, or
> set `XDOKU_DB_PORT` in `.env` to remap the host side.

**4. Build**

```bash
cmake -B build -S .
cmake --build build
```

**5. Run**

Run from one directory below the project root, since assets are loaded via relative paths:

```bash
cd build
./XDoku
```

### Windows

**1. Prerequisites**

- An MSVC toolset: Visual Studio, or the standalone
  [VS Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/) (just the compiler,
  no IDE needed).
- [CMake](https://cmake.org/download/) 3.30+ and [Ninja](https://github.com/ninja-build/ninja/releases)
  on `PATH`.
- [Docker Desktop](https://www.docker.com/products/docker-desktop/).
- [vcpkg](https://github.com/microsoft/vcpkg), bootstrapped, with:

  ```powershell
  vcpkg install glfw3:x64-windows-static-md libpqxx:x64-windows-static-md
  ```

  Use the `x64-windows-static-md` triplet, not the default `x64-windows` — the default builds a
  shared libpqxx whose import library collides (`LNK2005`) with this project's own object files.

**2. Configure environment**

```powershell
copy .env.example .env
```

**3. Database**

```powershell
docker compose up -d
```

Starts Postgres and applies migrations automatically (see [Migrations](#migrations)).

**4. Build**

Plain `cmake` won't work from a regular shell (no MSVC dev environment). Use
[`scripts\build-windows.bat`](scripts/build-windows.bat) instead:

```powershell
set VCPKG_ROOT=C:\path\to\your\vcpkg
scripts\build-windows.bat
```

Builds to `build\XDoku.exe`.

**5. Run**

```powershell
cd build
.\XDoku.exe
```

## Migrations

`docker compose up` applies migrations automatically via a one-off `migrations` container — no
Python needed on the host.

To author a *new* migration, Alembic needs to run locally against the SQLAlchemy models:

```bash
cd src/infrastructure/database/PostgreSQL/migrations
python3 -m venv .venv          # Windows: python -m venv .venv
source .venv/bin/activate      # Windows: .venv\Scripts\activate
pip install -r requirements.txt
alembic revision --autogenerate -m "describe the change"
```

The generated file under `alembic/versions/` is picked up automatically on the next
`docker compose up`.

## License

- **Code**: [MIT License](LICENSE-CODE.txt).
- **Content** (art, textures, sounds): [CC BY-NC 4.0](LICENSE-CONTENT.txt).
