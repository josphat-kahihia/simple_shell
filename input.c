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
 * @mark: Pointer to the last-written-to-byte on lp
 * @i: Pointer that scans the written lp
 * @br: read()'s byte count
 * @rv: The total byte counter
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
	if (*n < 1024 || *lp == NULL)
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
		if (*i == '\n') /* A conventional line, ending with \n*/
		{
			*lp = get_substring(*lp, i);
			return (br);
		}
		else if (*i != '\n' && *mark != '\n') /* EOF with content */
		{
			*lp = get_substring(*lp, mark);
			write(STDOUT_FILENO, "\n", 2);
			return (br);
		}
		if (br > ((ssize_t) *n - (br / 3)))
		{
			*lp = realloc_g_buff(*lp, n);
			if (*lp == NULL)
				return (-1);
			mark = *lp + (int)br;
		}
		mark++;
		i = mark;
		rv += br;
	}
	if (br <= 0 && rv == 0) /* EOF without content, problem with read() */
		return (-1);
	else if (br == 0 && rv > 0) /* EOF with content inside *lp */
		return (rv);
	return (-1);
}
