# Usable functions:
# readline, rl_clear_history, rl_on_new_line,
# rl_replace_line, rl_redisplay, add_history,
# printf, malloc, free, write, access, open, read,
# close, fork, wait, waitpid, wait3, wait4, signal,
# sigaction, sigemptyset, sigaddset, kill, exit,
# getcwd, chdir, stat, lstat, fstat, unlink, execve,
# dup, dup2, pipe, opendir, readdir, closedir,
# strerror, perror, isatty, ttyname, ttyslot, ioctl,
# getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
# tgetnum, tgetstr, tgoto, tputs


# Source for making a shell :
1.	 - https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
2.   - https://github.com/kamalmarhubi/shell-workshop
3.   - https://igupta.in/blog/writing-a-unix-shell-part-1/
4.   - https://github.com/tokenrove/build-your-own-shell
5.   - https://danishpraka.sh/posts/write-a-shell/
6.   - https://www.gnu.org/software/libc/manual/html_mono/libc.html#Implementing-a-Shell
7.   - https://aosabook.org/en/v1/bash.html

# ------------------------------------------------------------------------------------ #
# ------------------------------------------------------------------------------------ #
# ------------------------------------------------------------------------------------ #
# ------------------------------------------------------------------------------------ #


# TODO: Implement Executable Search and Launch

## Pseudo-code Outline

1. Get the PATH environment variable.
2. Split the PATH variable into individual directories.
3. For each directory in PATH:
	- Construct the full path to the executable.
	- Check if the file exists and is executable.
	- If found, break the loop.
4. If a relative or absolute path is provided:
	- Resolve the path if it's relative.
	- Check if the file exists and is executable.
5. If the executable is found:
	- Launch the executable.
6. Handle any errors if the executable is not found or cannot be launched.

Following these steps, you can implement a mechanism to search and launch the right executable based on the PATH variable or using a relative or absolute path.

## Steps

1. **Understand PATH**: ✅
	- The PATH environment variable contains directories where the system looks for executables.
	- Access the PATH variable in your code to get these directories.

2. **Split PATH**: ✅
	- Split the PATH variable into individual directories using the colon (:) as the delimiter.

3. **Check for Executable**: ✅
	- For each directory in PATH:
	  - Construct the full path by combining the directory path with the executable name.
	  - Check if the file exists and is executable.

4. **Handle Relative and Absolute Paths**: ✅
	- If a relative or absolute path is provided: 
	  - Resolve the path if it's relative.
	  - Check if the file exists and is executable.

5. **Launch the Executable**: ✅
	- Use a system call or library function to execute the program once the executable is found.

6. **Error Handling**: 
	- Handle errors gracefully if the executable is not found or if the path is invalid.

7. **Optional: Caching Results**: ✅
	- Cache the results of the executable search for efficiency.

# ------------------------------------------------------------------------------------ #
# ------------------------------------------------------------------------------------ #
# ------------------------------------------------------------------------------------ #
# ------------------------------------------------------------------------------------ #

# TODO : Check for valgrind errors. Actually having a lot of leak when ctrl+c\

1. **Checking where it leaks**
	- Use valgrind to see exactly what need to be freed.

2. **Fix it**
	- Just free the variables that need to be freed.
	- main.c (prompt) ✅
	- parser.c (command) ✅