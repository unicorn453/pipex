# Pipex

## Description

**Pipex** is a project that focuses on handling pipes in a Unix environment. The program mimics the shell's piping behavior, allowing data to be passed from one command to another using file descriptors.

It replicates the following shell command:

```sh
< file1 cmd1 | cmd2 > file2
```

where:

- `file1` is the input file.
- `cmd1` is the first command to execute.
- `cmd2` is the second command to execute.
- `file2` is the output file.

## Usage

### Compilation

Use the provided `Makefile` to compile the project:

```sh
make
```

This will generate the `pipex` executable.

### Execution

Run the program with the following syntax:

```sh
./pipex file1 "cmd1" "cmd2" file2
```

Example:

```sh
./pipex infile "ls -l" "wc -l" outfile
```

This is equivalent to:

```sh
< infile ls -l | wc -l > outfile
```

Another example:

```sh
./pipex infile "grep a1" "wc -w" outfile
```

Equivalent to:

```sh
< infile grep a1 | wc -w > outfile
```

## External Functions Used

The program relies on the following system calls:

- `open`, `close`, `read`, `write`
- `malloc`, `free`, `perror`, `strerror`, `access`
- `dup`, `dup2`, `execve`, `exit`, `fork`, `pipe`, `unlink`
- `wait`, `waitpid`

Additionally, `ft_printf` (or an equivalent function you coded) is allowed.

## Testing

### Basic Test Cases

Run the program with different commands to verify its behavior:

```sh
./pipex input.txt "cat" "wc -l" output.txt
```

Compare the output file with the shell command:

```sh
< input.txt cat | wc -l > output.txt
```

If they produce the same result, the implementation is correct.

### Edge Cases

- Test with non-existent files:
  ```sh
  ./pipex non_existent "ls -l" "wc -l" output.txt
  ```
- Test with commands that fail:
  ```sh
  ./pipex infile "invalid_command" "wc -l" outfile
  ```
- Test with permission errors:
  ```sh
  chmod 000 infile
  ./pipex infile "ls -l" "wc -l" outfile
  ```

### Memory Leak Check

Use `valgrind` to ensure no memory leaks:

```sh
valgrind --leak-check=full --track-fds=yes ./pipex infile "ls -l" "wc -l" outfile
```

## Conclusion

Pipex is a fundamental project that enhances understanding of process handling, file descriptors, and inter-process communication using pipes. Proper error handling and memory management are crucial for ensuring robustness and correctness.


