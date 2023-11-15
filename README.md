# Simple Shell

![Shell Logo](https://s3.amazonaws.com/intranet-projects-files/holbertonschool-low_level_programming/235/shell.jpeg)

## Table of Contents
- [Description](#description)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Command Examples](#command-examples)
- [Contributors](#contributors)
- [License](#license)

## Description
Simple Shell is a basic command-line interpreter program developed by Ayoub Draid and Salwa Naciri. It provides a simplified interface for users to interact with the operating system. The shell allows users to execute various commands and provides basic shell functionalities such as executing programs, managing files and directories, and handling input/output redirection.

## Features
- **Command Execution:** The shell can execute both built-in commands and external programs.
- **Input/Output Redirection:** Users can redirect the input and output of commands to files.
- **Piping:** Users can pipe the output of one command as the input to another command.
- **Background Execution:** Commands can be executed in the background by appending an ampersand (&) at the end of the command.
- **Environment Variable Handling:** The shell supports environment variables and allows users to set, get, and delete them.
- **Signal Handling:** The shell handles common signals such as SIGINT (Ctrl+C) and SIGTSTP (Ctrl+Z).
- **Command History:** Users can access previous commands using the arrow keys or by typing !! to execute the last command.

## Installation
1. Clone the repository:
$ git clone https://github.com/Kroser-draid/simple_shell.git
2. Compile the source code:
$ gcc -Wall -Werror -Wextra -pedantic *.c -o shell
## Usage
1. Run the shell:
$ ./shell
2. Use the shell by entering commands. For example:
$ ls
$ echo "Hello, World!"
$ cat file.txt
## Command Examples
- Execute an external program:
$ ls
- Execute a built-in command:
$ cd /path/to/directory
- Redirect output to a file:
$ ls > output.txt
- Pipe the output of one command to another:
$ ls | grep "pattern"
- Run a command in the background:
$ sleep 10 &
- Set an environment variable:
$ export MY_VARIABLE=value

## Contributors
- Ayoub Draid - @Kroser-draid
- Salwa Naciri - @SalwaN23

## License
This project is licensed under the MIT License.

---

**About**

The "Simple Shell" repository is a collaborative project developed by Kroser_draid and SalwaN23 as part of the ALX Software Engineering program. This project aims to recreate the functionality of the standard C library function "printf" in order to provide a custom implementation of this essential utility.