#include "main.h"

/**
 * _strlen - alternate implementation of strlen
 * @s: The string
 *
 * Return: Length of the string (Exclusive of '\0')
 */
size_t _strlen(char *s)
{
	size_t i;

	for (i = 0; s[i] != '\0'; i++)
		;
	return (i);
}

/**
 * _strcpy - alternate implementation of strcpy
 * @dest: The string to be copied into
 * @src: The string to copy from
 *
 * Return: dest
 */
char *_strcpy(char *dest, const char *src)
{
	int i;

	if (dest == NULL || src == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * get_substring - get the substring
 * @start: The starting point
 * @end: The end of the substring
 * str: the string
 * i: counter
 * p: the moving pointer
 *
 * Usage: Provide a starting point, and optionally, an end point. If an end
 * is provided, it copies everthing between start and end (both inclusive).
 * If end is not supplied (i.e.: end == NULL), it copies everything until it
 * finds a '\0' byte. It prepends a '\0' to the end of the string if end is
 * not one.
 *
 * Return: substring on success, NULL on error
 */
char *get_substring(char *start, char *end)
{
	char *str;
	char *p;
	int i;
	int len;

	if (start == NULL)
		return (NULL);
	if (end == NULL)
	{
		len = _strlen(start) + 1;
		str = malloc(sizeof(char) * len);
		if (str == NULL)
			printf("Error in malloc!");
		str = _strcpy(str, start);
		return (str);
	}
	p = start;
	len = 0;
	while ((p + len) <= end)
		len++;
	str = malloc(sizeof(char) * ++len);
	if (!str)
		return (NULL);
	i = 0; /* Alternatively, use start and end as they are copies */
	while ((p + i) <= end)
	{
		str[i] = p[i];
		i++;
	}
	if (*end != '\0')
		str[i] = '\0';
	return (str);
}

/**
 * _strconcat - Alternate implementation of strcat
 * @dest: The altered string
 * @src: The source string
 * @p: Pointer to start of copying
 *
 * Return: Pointer to dest
 */
char *_strconcat(char *dest, char *src)
{
	char *p;

	p = dest;
	while (*p != '\0')
		p++;
	p = _strcpy(p, src);
	if (p == NULL)
		return (NULL);
	return (dest);
}

