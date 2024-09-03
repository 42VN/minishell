# Shell Development: Allowed Functions

## Input Handling
These functions help in reading user input and managing the command line interface.

- **`readline(char *prompt)`**: Reads a line of input from the user, displaying the prompt.
- **`rl_clear_history()`**: Clears the command history.
- **`add_history(char *line)`**: Adds the given line to the command history.
- **`rl_on_new_line()`**: Resets the internal state to indicate a new line.
- **`rl_replace_line(const char *text, int clear_undo)`**: Replaces the current input line with the given text.
- **`rl_redisplay()`**: Refreshes and redraws the input line on the screen.

## Output Handling
These functions help in printing formatted output to the user.

- **`printf(const char *format, ...)`**: Prints formatted output to standard output.
- **`write(int fd, const void *buf, size_t count)`**: Writes `count` bytes from `buf` to the file descriptor `fd`.

## Memory Management
These functions manage dynamic memory allocation in your shell.

- **`malloc(size_t size)`**: Allocates `size` bytes of memory.
- **`free(void *ptr)`**: Frees the memory previously allocated by `malloc`.

## File and Directory Handling
These functions interact with the file system, handling files and directories.

- **`open(const char *pathname, int flags)`**: Opens a file and returns a file descriptor.
- **`close(int fd)`**: Closes the file descriptor `fd`.
- **`read(int fd, void *buf, size_t count)`**: Reads `count` bytes from `fd` into `buf`.
- **`access(const char *pathname, int mode)`**: Checks the access permissions for the file at `pathname`.
- **`unlink(const char *pathname)`**: Deletes the file at `pathname`.
- **`getcwd(char *buf, size_t size)`**: Gets the current working directory and stores it in `buf`.
- **`chdir(const char *path)`**: Changes the current working directory to `path`.
- **`stat(const char *pathname, struct stat *statbuf)`**: Retrieves information about the file at `pathname`.
- **`lstat(const char *pathname, struct stat *statbuf)`**: Retrieves information about the link itself rather than the file it points to.
- **`fstat(int fd, struct stat *statbuf)`**: Retrieves information about the file referred to by `fd`.
- **`opendir(const char *name)`**: Opens the directory stream for `name`.
- **`readdir(DIR *dirp)`**: Reads the next entry in the directory stream `dirp`.
- **`closedir(DIR *dirp)`**: Closes the directory stream.

## Process Management
These functions create and manage processes.

- **`fork()`**: Creates a new process by duplicating the calling process.
- **`wait(int *status)`**: Waits for a child process to terminate.
- **`waitpid(pid_t pid, int *status, int options)`**: Waits for a specific child process to terminate.
- **`wait3(int *status, int options, struct rusage *rusage)`**: Waits for a child process to terminate and provides resource usage information.
- **`wait4(pid_t pid, int *status, int options, struct rusage *rusage)`**: Similar to `waitpid` but also returns resource usage information.
- **`kill(pid_t pid, int sig)`**: Sends the signal `sig` to the process with ID `pid`.
- **`exit(int status)`**: Terminates the current process with the given exit status.
- **`execve(const char *pathname, char *const argv[], char *const envp[])`**: Replaces the current process image with a new one.

## Signal Handling
These functions manage and respond to signals within your shell.

- **`signal(int signum, sighandler_t handler)`**: Sets a handler function for the signal `signum`.
- **`sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)`**: Examines and changes the action taken on receipt of a specific signal.
- **`sigemptyset(sigset_t *set)`**: Initializes the signal set `set` to be empty.
- **`sigaddset(sigset_t *set, int signum)`**: Adds the signal `signum` to the signal set `set`.

## Terminal Handling
These functions interact with and control terminal behavior.

- **`isatty(int fd)`**: Checks if the file descriptor `fd` refers to a terminal device.
- **`ttyname(int fd)`**: Returns the name of the terminal connected to `fd`.
- **`ttyslot()`**: Returns the index of the current terminal.
- **`ioctl(int fd, unsigned long request, ...)`**: Performs device-specific I/O operations on the file descriptor `fd`.
- **`tcgetattr(int fd, struct termios *termios_p)`**: Gets the parameters associated with the terminal referred to by `fd`.
- **`tcsetattr(int fd, int optional_actions, const struct termios *termios_p)`**: Sets the parameters associated with the terminal referred to by `fd`.

## Environment Variables
These functions access and modify the shell environment.

- **`getenv(const char *name)`**: Retrieves the value of the environment variable `name`.

## Termcap Library Functions
These functions interact with the terminal capability database.

- **`tgetent(char *bp, const char *name)`**: Gets the terminal entry for the terminal type `name`.
- **`tgetflag(char *id)`**: Gets the value of the boolean capability `id`.
- **`tgetnum(char *id)`**: Gets the numeric value of the capability `id`.
- **`tgetstr(char *id, char **area)`**: Gets the string value of the capability `id`.
- **`tgoto(const char *cap, int col, int row)`**: Returns a cursor movement string for the terminal.
- **`tputs(const char *str, int affcnt, int (*putc)(int))`**: Outputs the string `str` to the terminal, considering padding information.

## Error Handling
These functions help handle errors within the shell.

- **`strerror(int errnum)`**: Returns a string describing the error code `errnum`.
- **`perror(const char *s)`**: Prints a description of the last error that occurred, prefixed by the string `s`.
