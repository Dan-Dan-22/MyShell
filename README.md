# mysh

A minimal Unix shell written in C from scratch, built as a hands-on way to
learn how operating systems create and manage processes.

## Features

- Interactive prompt with a read–parse–execute loop
- Runs any external program found in `PATH`, with arguments (`ls -l /tmp`)
- Built-in commands, dispatched through a table of function pointers:
  - `cd [dir]` changes the shell's own working directory (goes to `$HOME` with no argument)
  - `help` lists the available built-ins
  - `quit` exits the shell

## Build and run

```bash
gcc -Wall -Wextra -g myshell.c -o myshell
./myshell
```

```
myshell> ls -l
myshell> cd /tmp
myshell> pwd
myshell> quit
```

## Concepts practiced

- Process creation and control: `fork`, `execvp`, `waitpid`
- Process states, parent/child relationship and zombie reaping
- Working directory as per-process state (`chdir`)
- Command-line parsing and `NULL`-terminated argument arrays
- Pointers, arrays of strings and function pointers in C
- Debugging segmentation faults with `gdb`

## Context

Written while studying Operating Systems (processes, limited direct execution,
system calls) at Roma Tre University.
