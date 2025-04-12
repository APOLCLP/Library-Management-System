# Library Management System (LMS)

A C++ project demonstrating core Object-Oriented Programming (OOP) principles—**abstraction**, **inheritance**, **polymorphism**, and **encapsulation**—to manage library operations effectively.


## 📁 Project Structure

- **`src/`**: Contains the main application logic.
  - `main.cpp`: Entry point of the application.
  - `class.hpp`: Defines all classes and their attributes.
- **`dataset/`**: Holds real data files used by the system.
- **`docs/`**: Includes documentation. Start with `Library-guide` for usage instructions.
- **`update_days/`**: Manages borrowing durations.
  - `updat.py`: Updates the number of days books have been borrowed.
  - `last_run_date.txt`: Records the last date the update script was executed.

## 🚀 Getting Started

1. **Clone the repository**:
   ```bash
   git clone https://github.com/APOLCLP/Library-Management-System.git

2. **Navigate to the project directory**:
   ```bash
	cd Library-Management-System
3. **Compile the application**:
   ```bash
	g++ src/main.cpp -o lms
4. **Run the application**:
   ```bash
	./lms
5. **Update borrowing durations**:
	```bash
	python3 update_days/updat.py
## 📚 Usage

- Before using the system, read the `Library-guide` in the `docs/` directory for detailed instructions.
- Ensure the `dataset/` directory contains the necessary data files.
- Run `updat.py` periodically to keep borrowing durations up to date.
## 🛠️ Features

-   User-friendly command-line interface for managing library operations.
-   Efficient tracking of borrowed books and their durations.​
-   Modular codebase demonstrating best practices in OOP.
