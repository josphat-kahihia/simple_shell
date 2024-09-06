#include "main.h"

/**
 * execute_commands - Run the commands
 * @token: the current command
 * @argv: the child's argv
 * @pid: the child's pid
 * @pid2: for comparison purposes
 * @s: exit value
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
 * be any program, as long as it is in PATH.
 *
 * References: man(2) wait, man(2) fork, man(2) getpid, man(2) execve, man(5)
 * proc
 *
 * Links(in_their_respective_orders):
 * https://man7.org/linux/man-pages/man2/waitpid.2.html
 * https://man7.org/linux/man-pages/man2/fork.2.html
 * https://man7.org/linux/man-pages/man2/getpid.2.html
 * https://man7.org/linux/man-pages/man2/execve.2.html
 * https://man7.org/linux/man-pages/man5/proc.5.html
 *
 * Did_you_know?: A child process can remove itself from the original Process
 * Group ID (PGID), and create a new one where it is the leader. Oh, the
 * opportunities that brings!
 *
 * Return: the status code if failure, 0 on successs
 */
int execute_commands(char *token , char **env)
{
	char **argv;
	pid_t pid;
	pid_t pid2;
	int s;

	pid = fork();
	if (pid == -1) /* fork failed, in parent (shell) */
	{
		printf("argv[0]: fork: {perror()}");
		return (-1);
	}
	if (pid == 0) /* Inside the child */
	{
		argv = malloc(sizeof(char *) * 2); /* Only one token rn */
		if (argv == NULL)
			_exit(-1); /* Since return would go to child's main*/
		argv[0] = malloc(sizeof(char) * (_strlen(token) +1));
		argv[0] = _strcpy(argv[0], token);
		argv[1] = NULL;
		if (argv[0] == NULL)
			_exit(-1);
		if(execve(argv[0], argv, env) == -1)
		{
			perror("./sh"); /* should actually be shell's argv[0] */
			_exit(-1);
		}
	}
	else if (pid > 0) /* Inside the parent (shell) */
	{
		pid2 = waitpid(pid, &s, 0);
		if (pid != pid2)
			perror("Wut Just Happened?");
		if (WIFEXITED(s))
		{
			s = WEXITSTATUS(s);
			/* printf("%s _exited success with %i\n", token, s); */
			return (s);
		}
	} /* technically, this can be outside the else block */
	return (-1); /* Can only get here as a result of an error */
}
