#include "main.h"

/**
 * prompt - prints a prompt
 * @s: The prompt string
 */
void prompt(char *s)
{
	if (s == NULL)
		s = "$ ";
	write(STDOUT_FILENO, s, (_strlen(s) + 1));
}

/**
 * _getline - Alternate implementation of getline()
 * @lp: The buffer
 * @n: Pointer to size of the buffer
 * @fd: The file descriptor
 *
 * Description: This function is similar to getline() (see man getline()),
 * with the major difference being instead of using a `FILE *` struct, we
 * are using `int fd` to be compatible with the read() system call.
 *
 * Return: Bytes read on success, -1 on failure or EOF, -2 if lp is NULL
 */
ssize_t _getline(char **lp, size_t *n, int fd)
{
	char *mark;
	char *i;
	ssize_t br; /* read's byte count */
	ssize_t rv; /* total byte counter */

	if (lp == NULL)
		return (-2);
	*lp = realloc_g_buff(*lp, n); /* sets the default n to 1024 */
	if (*lp == NULL)
		return (-1);
	i = *lp;
	mark = *lp;
	rv = 0;
	br = read(fd, mark, *n);
	while (br > 0)
	{
		mark += (int)br;
		while (*i != '\n' && i++ <= mark)
			;
		if ((*i == '\n') || (*i != '\n' && *mark != '\n'))
		{
			*lp = _getline_helper(lp, i, mark);
			return (br);
		}
		if (br > ((ssize_t) *n - (br / 3)))
		{
			*lp = realloc_g_buff(*lp, n);
			if (*lp == NULL)
				return (-1);
			mark = *lp + (int)br;
		}
		rv = _getline_setter(mark, i, rv, br);
	}
	if (br <= 0 && rv == 0) /* EOF without content, problem with read() */
		return (-1);
	else if (br == 0 && rv > 0) /* EOF with content inside *lp */
		return (rv);
	return (-1);
}

/**
 * get_input - wrapper function for _getline
 * @cmd_main: struct commands_centre
 *
 * Return: gr
 */
ssize_t get_input(commands_centre *cmd_main)
{
	char *line;
	size_t n;
	ssize_t gr;

	line = NULL;
	cmd_main->cl = &line;
	n = 0;
	gr = _getline(cmd_main->cl, &n, cmd_main->fd);
	return (gr);
}
