#include "main.h"

/**
 * execute_commands - Run the commands
 * @cmd_main: [temporary] holds the exec name
 * @tokens: execve()'s argv
 * @env: environ
 *
 * Description: This function introduces fairly new concepts. We have execve,
 * that replaces the thread in a process with a new program, and waitpid/sister
 * functions. There are 4 variants of wait, each with their own importance. I
 * chose waitpid() to closely emulate current software models that (I think?)
 * open and manage various child processes, with a few specific sensitive
 * processes that upon status change, the parent jumps in to handle the
 * situation (eg, Antivirus noting that a background update process has been
 * terminated, A browser noting that a critical resource manager has been
 * closed, etc). Fork is rather straightforward as it spawns the various child
 * processes needed, returning the child's actual PID to the parent, and `0` to
 * the child. This doesnt mean that the child cannot see it's PID (or PPID
 * even). See "References" below.
 *
 * Note: execve() requires that the pathname resolves to a binary or an
 * executable shell script whose first line is `#! interpreter`. The shell can
 * be any program, as long as it is in PATH. Why _exit() and not exit() in the
 * child process? To ensure the child process terminates cleanly and without
 * affecting the parent process’s environment.
 *
 * References: man(2) wait, man(2) fork, man(2) getpid, man(2) execve, man(5)
 * proc man(3) exit, man(3) _exit
 *
 * Links(in_their_respective_orders): Had to remove https from them to silence
 * betty's errors.
 * man7.org/linux/man-pages/man2/waitpid.2.html
 * man7.org/linux/man-pages/man2/fork.2.html
 * man7.org/linux/man-pages/man2/getpid.2.html
 * man7.org/linux/man-pages/man2/execve.2.html
 * man7.org/linux/man-pages/man5/proc.5.html
 * man7.org/linux/man-pages/man3/exit.3.html
 * man7.org/linux/man-pages/man2/exit.2.html
 *
 * Did_you_know?: A child process can remove itself from the original Process
 * Group ID (PGID), and create a new one where it is the leader. Oh, the
 * opportunities that brings!
 *
 * Return: the status code if failure, 0 on successs
 */
int execute_commands(commands_centre *cmd_main, char **tokens, char **env)
{
	char **argv;
	pid_t pid;
	pid_t pid2;
	char *err;
	int s;

	err = err_string(cmd_main, tokens[0]);
	if (err == NULL)
		return (-1);
	pid = fork();
	if (pid == -1) /* fork failed, in parent (shell) */
	{
		perror(cmd_main->execname);
		return (-1);
	}
	if (pid == 0) /* Inside the child */
	{
		argv = tokens;
		if (execve(argv[0], argv, env) == -1)
		{
			perror(err); /* Shell's argv[0] */
			_exit(-1);
		}
	}
	/* Inside the parent (shell) */
	pid2 = waitpid(pid, &s, 0);
	if (pid != pid2)
	{
		perror("Wut Just Happened?");
		exit(-1);
	}
	if (WIFEXITED(s))
	{
		s = WEXITSTATUS(s);
		return (s); /* The exit status */
	}
	return (-1); /* Can only get here as a result of an error */
}
