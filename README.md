# GatorsKitchen 🐊🍽️

**CEN3031 Project Group 13**

## Project Vision

For students who need a fast and trustworthy way to find food assistance. GatorsKitchen is a web-based service that provides a more curated and location-focused directory vs general web searches. Unlike other services or package software products, our product service provides a verified list of resources specifically accessible with a student ID.

## Features

- **Student ID Authentication:** Integrates with university authentication systems to ensure resources are provided only to verified students.
- **Real-Time Availability & Inventory:** Displays the current operating status and inventory of pantries in real-time to prevent wasted trips.
- **Dietary & Allergy Filters:** Allows users to search for pantries that accommodate specific dietary needs, including halal, kosher, vegan, and allergy-friendly options.
- **Distance Filtering & Navigation:** Filters pantries based on distance from the user's current location and seamlessly integrates with Google Maps and Apple Maps for routing and navigation.

## Tech Stack

- **Languages:** C++, Python
- **Database:** MySQL (production) / SQLite (development prototype)
- **External Integrations:**
  - External Map (Google Maps / Apple Maps redirection)
  - Student Authentication System

## Prerequisites

To ensure a consistent development environment, this project is developed on **Ubuntu**.

### Required Tools
1. **Ubuntu / WSL2 (Ubuntu)**: Required for C++ build tools and general development.
   ```bash
   # Windows users: Install WSL and Ubuntu (Run in PowerShell as Administrator)
   wsl --install -d Ubuntu
   ```

2. **Docker**: Used for spinning up the local MySQL database environment consistently. Please follow the installation instructions on the [official Docker website](https://docs.docker.com/get-docker/).

3. **uv**: A fast Python package manager and environment resolver.
   ```bash
   # Install uv (Linux/macOS/WSL)
   curl -LsSf https://astral.sh/uv/install.sh | sh
   ```

4. **Python**: Required for running Python.
   ```bash
   sudo apt update && sudo apt install python3 python3-venv python3-dev
   ```
   **Check the version of Python**: Check if Python is installed correctly.
   ```bash
   python3 --version
   ```

5. **CMake**: Required for generating build system from `CMakeLists.txt`.
   ```bash
   sudo apt update && sudo apt install cmake
   ```

6. **C++ Build Tools**: Required for local C++ compilation.
   ```bash
   # Install essential build tools
   sudo apt update && sudo apt install build-essential
   ```
   
7. **C++ Formatting & Linting Tools**: Required for `make format` and `make lint` commands to format and lint C++ code.
   ```bash
   # Install clang-format and clang-tidy (version 17)
   sudo apt install clang-format-17 clang-tidy-17
   sudo update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-17 100
   sudo update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-17 100
   ```

## Installation & Setup

1. **Clone the repository:**
   ```bash
   git clone https://github.com/ksolber/CEN3031-Project.git
   ```

2. **Environment Variables:**
   Create a `.env` file in the root directory and configure your API keys and database credentials. Defaults for local Docker development:
   ```env
   DB_HOST=127.0.0.1
   DB_PORT=3306
   DB_USER=root
   DB_PASSWORD=root_password
   DB_NAME=gatorskitchen
   ```

3. **Database Setup (Docker):**
   Start the local MySQL database container in the background:
   ```bash
   docker compose up -d
   ```
   To verify the container is running:

   ```bash
   docker compose ps
   ```

4. **Python Dependencies (uv):**
   Set up Python environment and install dependencies:
   ```bash
   uv sync
   ```

5. **Build System Setup (CMake):**
   Generate the build system (e.g., Makefiles) from `CMakeLists.txt`.
   ```bash
   cmake -B build -S .
   ```

## Ports

| Port | Service              |
|------|----------------------|
| 3306 | MySQL (database)     |
| 8000 | FastAPI (web server) |

## Formatting & Linting

Before committing, please make sure to run the formatting and linting checks:

```bash
# Format C++ and Python code
make format
# Lint C++ and Python code
make lint
```

## Testing & Running

To run the automated tests for the project:
```bash
make test
```

To start the FastAPI development server:

```bash
uv run task dev
```

The API will be available at `http://localhost:8000`.

To build and run the main application:
```bash
# Build the application
make build

# Run the application
make run
```

## Development Guidelines

### Branch Naming

`name/type/short-description` (e.g., `john/feature/add-filter-logic`)

### Commit Messages

`type: brief description` (e.g., `feature: implement filter logic`)

### Types

- `feature` — New features
- `fix` — Bug fixes
- `refactor` — Code improvements (without changing functionality)
- `docs` — Documentation updates
- `chore` — Maintenance tasks (dependencies, build tools, config)
