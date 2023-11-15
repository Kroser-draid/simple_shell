#include "shell.h"

/**
*_my_strcpy - copies a string
*@dest: the destination
*@src: the source
*
*Return: pointer to destination
*
*/
char *_my_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
*_my_strdup - duplicates a string
*@str: the string to duplicate
*
*Return: pointer to the duplicated string
*
*/
char *_my_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
*_my_puts - prints an input string
*@str: the string to be printed
*
*Return: nothing
*
*/
void _my_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_my_putchar(str[i]);
		i++;
	}
}

/**
*_my_putchar - writes the character c to stdout
*@c: the character to be printed
*
*Return: on success 1, -1 on error, and errno is set
*
*/
int _my_putchar(char c)
{
		static int i;
		static char buf[MY_WRITE_BUF_SIZE];

		if (c == MY_BUF_FLUSH || i >= MY_WRITE_BUF_SIZE)
		{
			write(1, buf, i);
			i = 0;
		}
		if (c != MY_BUF_FLUSH)
			buf[i++] = c;
		return (1);
}
