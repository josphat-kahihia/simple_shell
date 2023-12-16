#include "myShell.h"

/**
* _strcmp - compare two strings
* @s1: string 1
* @s2: string 2
* Return: int that tells num spaces in between, 0 if exactly the same string
*/
/*#include <stdbool.h>*/
int _strcmp(const char *s1, const char *s2)
{

        while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}

	if (*s1 == '\0' && *s2 == '\0')
	{
		return (0);
	}
	else
	{
		return ((*s1 == '\0') ? -1 : 1);
	}
}
/*int i = 0;
while (s1[i] != '\0' && s1[i] == s2[i])
i++;
if (s2[i] != '\0')
return (s1[i] - s2[i]);
else
return (0);*/