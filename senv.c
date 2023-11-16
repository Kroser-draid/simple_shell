#include "shell.h"

/**
*_my_env - prints the current my_environment
*@info: structure containing potential arguments. used to maintain
*
*Return: Always 0.
*
*/
int _my_env(my_info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
*_my_getenv - gets the value of an my_environ variable
*@info: structure containing potential arguments. used to maintain
*@name: env var name
*
*Return: the value
*
*/
char *_my_getenv(my_info_t *info, const char *name)
{
	my_list_t *node = info->env;
	char *p;

	while (node)
	{
		p = my_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
*_my_setenv - initialize a new my_environment variable, or modify
*@info: structure containing potential arguments. used to maintain
*
*Return: Always 0
*
*/
int _my_setenv(my_info_t *info)
{
	if (info->argc != 3)
	{
		_my_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
*_my_unsetenv - remove an my_environment variable
*@info: structure containing potential arguments. used to maintain
*
*Return: Always 0
*
*/
int _my_unsetenv(my_info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_my_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
*populate_env_list - populates env linked list
*@info: structure containing potential arguments. used to maintain
*
*Return: Always 0
*
*/
int populate_env_list(my_info_t *info)
{
	my_list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
