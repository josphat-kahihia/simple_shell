#include "myShell.h"

/**
 * _stringChr- checks for character c in the string given
 * @s: pointer to sring s
 * @c: the charcter to be found
 * Return: chracter c when found else null
 **/
char *_stringChr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (s);
		}
		s++;
	}
	return (NULL);
}