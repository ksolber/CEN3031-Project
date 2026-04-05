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
- **Database:** MySQL
- **External Integrations:** 
  - External Map URL Schemes (Google Maps / Apple Maps redirection)
  - Student Authentication System

## Prerequisites

To run this project locally, you will need:
- C++ compiler
- Python
- MySQL Server

## Installation & Setup

1. **Clone the repository:**
   ```bash
   git clone https://github.com/ksolber/CEN3031-Project.git
   cd CEN3031-Project
   ```

2. **Database Setup:**
   - Ensure MySQL is running and set up the required databases and tables (e.g., executing setup SQL scripts).

3. **Environment Variables:**
   - Create a `.env` file in the root directory and configure your API keys and database credentials.

4. **Build and Run:**
   Currently, the project is in the testing phase. You can build and run the tests using:
   ```bash
   make test
   ```

## Testing

To run the automated tests for the project (e.g., pantry status tests):
```bash
make test
```

## Development Guidelines

- **Branch Naming**: `name/type/short-description`
  - `feature`: New features (e.g., `name/feature/add-login`)
  - `bugfix`: Bug fixes (e.g., `name/bugfix/db-connection`)
  - `refactor`: Code improvements (without changing functionality)
  - `docs`: Documentation updates
- **Pull request & Commit Messages**: `type: brief description`
  - `feature:` A new feature
  - `fix:` A bug fix
  - `docs:` Documentation changes
  - `refactor:` Code improvements
