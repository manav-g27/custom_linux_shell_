# 🐚 POSIX C++ Linux Shell

<div align="center">

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![Linux](https://img.shields.io/badge/Platform-Linux-green.svg)
![POSIX](https://img.shields.io/badge/POSIX-Compliant-orange.svg)
![Build](https://img.shields.io/badge/Build-Make-red.svg)
![Docker](https://img.shields.io/badge/Docker-Supported-2496ED?logo=docker)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

*A production-oriented Unix Shell built from scratch using C++ and POSIX system calls.*

</div>

---

## 📖 Overview

This project is a **custom Linux shell** implemented in **Modern C++17** using low-level POSIX APIs. It demonstrates how a Unix shell manages processes, executes commands, performs inter-process communication, redirects I/O, and handles signals.

Unlike a basic shell implementation, this project focuses on **operating system concepts**, **systems programming**, and **production-style engineering practices** including automated builds, Docker support, testing, and CI/CD.

---

# ✨ Features

## Command Execution

- Execute external Linux commands
- Built using `fork()`
- Program replacement using `execvp()`
- Parent-child synchronization using `wait()` and `waitpid()`

---

## Built-in Commands

Supports native shell commands executed inside the shell process:

- `cd`
- `pwd`
- `echo`
- `history`
- `export`
- `exit`
- `jobs`

---

## Pipes

Supports

```bash
ls | grep cpp
```

Multiple pipes

```bash
cat file.txt | grep hello | wc -l
```

Implemented using

- `pipe()`
- `dup2()`

---

## I/O Redirection

Input

```bash
cat < input.txt
```

Output

```bash
echo Hello > output.txt
```

Append

```bash
echo Hello >> output.txt
```

Combination

```bash
cat < input.txt | grep Linux > output.txt
```

---

## Background Jobs

Supports

```bash
sleep 30 &
```

View jobs

```bash
jobs
```

Foreground

```bash
fg
```

Background

```bash
bg
```

---

## Signal Handling

Implemented

- SIGINT (Ctrl+C)
- SIGTSTP (Ctrl+Z)
- SIGCHLD

Features

- Prevent shell termination
- Foreground process interruption
- Zombie process cleanup
- Background job management

---

## Memory Safety

- Proper file descriptor cleanup
- Safe resource management
- Valgrind tested
- Leak-free execution

---

## Docker Support

Run the shell without installing dependencies.

```bash
docker build -t myshell .
docker run -it myshell
```

---

## Automated Testing

Includes test scripts covering

- Command execution
- Built-ins
- Pipes
- Redirection
- Background jobs

Run

```bash
make test
```

---

## CI/CD

GitHub Actions automatically

- Builds project
- Runs tests
- Performs Valgrind analysis

---

# 🏗 Architecture

```
                   User Input
                        │
                        ▼
                +----------------+
                |    Parser      |
                +----------------+
                        │
                        ▼
             Command Representation
                        │
        ┌───────────────┴───────────────┐
        │                               │
        ▼                               ▼
 Built-in Commands             External Commands
        │                               │
        ▼                               ▼
 Execute in Parent           fork()
                                     │
                                     ▼
                                Child Process
                                     │
                          +----------+----------+
                          |                     |
                          ▼                     ▼
                    dup2() / pipe()        execvp()
                                     │
                                     ▼
                               Linux Kernel
```

---

# 📂 Project Structure

```
.
├── main.cpp
├── parser.cpp
├── parser.h
├── executor.cpp
├── executor.h
├── jobs.cpp
├── jobs.h
├── Makefile
├── Dockerfile
├── test_shell.sh
├── README.md
└── .github
    └── workflows
        ├── ci.yml
        └── release.yml
```

---

# ⚙️ Build

Clone

```bash
git clone https://github.com/manav-g27/custom_linux_shell_.git
```

Enter directory

```bash
cd custom_linux_shell_
```

Compile

```bash
make
```

Run

```bash
./myshell
```

Install globally

```bash
sudo make install
```

Clean

```bash
make clean
```

---

# 🧪 Example Commands

### Execute

```bash
ls
```

### Pipe

```bash
ls -l | grep cpp
```

### Multiple Pipes

```bash
cat file.txt | grep hello | wc -l
```

### Output Redirection

```bash
echo Hello > file.txt
```

### Append

```bash
echo World >> file.txt
```

### Input

```bash
cat < file.txt
```

### Background

```bash
sleep 20 &
```

### Jobs

```bash
jobs
```

---

# 🐳 Docker

Build

```bash
docker build -t myshell .
```

Run

```bash
docker run -it myshell
```

---

# 🧪 Testing

```bash
make test
```

---

# 📊 CI Pipeline

GitHub Actions automatically

- Build
- Test
- Run Valgrind
- Verify memory safety

---

# 🎥 Demo

> **Demo GIF**

Add your terminal recording here.

Recommended:

- asciinema
- GIF
- MP4

Example

```
https://asciinema.org/a/6CaITUsNR3GASsvY
```

---

# 📚 Operating System Concepts Demonstrated

- Process Creation
- Process Lifecycle
- Process Synchronization
- Process Groups
- Pipes
- File Descriptors
- I/O Redirection
- Signals
- Zombie Process Handling
- Foreground & Background Jobs
- POSIX APIs
- Linux System Calls

---

# 🛠 Technologies Used

- C++17
- POSIX System Calls
- Linux
- Make
- Docker
- GitHub Actions
- Valgrind

---

# 🚀 Future Improvements

- Command history persistence
- Auto-completion
- Environment variable expansion
- Alias support
- Wildcard expansion
- Shell scripting support
- Custom prompt
- Configuration file

---

# 👨‍💻 Author

**Manav Gupta**

- GitHub: https://github.com/manav-g27
- LinkedIn: https://linkedin.com/in/manavgupta27

---

## ⭐ If you found this project useful, consider giving it a Star!
