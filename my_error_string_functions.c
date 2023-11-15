#include "shell.h"

/**
*_my_eputs - prints an input string
*@str: the string to be printed
*
*Return: nothing
*
*/
void _my_eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_my_eputchar(str[i]);
		i++;
	}
}

/**
*_my_eputchar - writes the character c to stderr
*@c: the character to print
*
*Return: on success 1.
*on error, -1 is returned, and errno is set appropriatly.
*
*/
int _my_eputchar(char c)
{
	static int i;
	static char buf[MY_WRITE_BUF_SIZE];

	if (c == MY_BUF_FLUSH || i >= MY_WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != MY_BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
*_my_putfd - writes the character c to given fd
*@c: the character to print
*@fd: the filedescriptor to write to
*
*Return: on success 1.
*on error, -1 is returned, and errno is set appropriatly.
*
*/
int _my_putfd(char c, int fd)
{
	static int i;
	static char buf[MY_WRITE_BUF_SIZE];

	if (c == MY_BUF_FLUSH || i >= MY_WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != MY_BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
*_my_putsfd - prints an input string
*@str: the string to be printed
*@fd: the filedescriptor to write to
*
*Return: the number of chars put
*
*/
int _my_putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _my_putfd(*str++, fd);
	}
	return (i);
}
