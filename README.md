# CMan - CMake Manager

CMan is a simple CLI tool that abstracts CMake complexities for users who want portability without the hassle of managing CMake files manually.

## Features

- **Init**: Initialize a new project with a standard CMake configuration.
- **Build**: Configure and build your project with a single command.
- **Run**: Run your compiled application.
- **Add**: Add new C++ source files to your project and automatically update `CMakeLists.txt`.

## Build & Installation

1. Clone the repository.
2. Build the tool using CMake:
   ```bash
   cmake -S . -B build
   cmake --build build
   ```
3. The executable will be in `build/Debug/cman.exe` (on Windows). Add this to your PATH for easy access.

## Usage

### Initialize a Project
```bash
cman init [ProjectName]
```
If no name is provided, it prompts for one. Creates `CMakeLists.txt` and `src/main.cpp`.

### Build the Project
```bash
cman build
```
Runs `cmake` configuration and build steps.

### Run the Application
```bash
cman run [args...]
```
Executes the built binary.

### Add a File
```bash
cman add src/my_file.cpp
```
Creates the file (if it doesn't exist) and adds it to the `add_executable` list in `CMakeLists.txt`.
