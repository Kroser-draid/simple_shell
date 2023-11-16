#include "shell.h"
/**
*get_environ - returns the string array copy of our my_environ
*@info: structure containing potential arguments. used to maintain
*
*Return: always 0
*
*/
char **get_environ(my_info_t *info)
{
	if (!info->my_environ || info->env_changed)
	{
		info->my_environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->my_environ);
}

/**
*_unsetenv - remove my_environment variables
*@info: structure containing potential arguments. used to maintain
*
*Return: the string env var property
*@var: the string env var property
*
*/
int _unsetenv(my_info_t *info, char *var)
{
	my_list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = my_starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
*_setenv - initialize a new my_environment variable, or modify
*@info: structure containing potential arguments, used to maintain
*@var: the string env var property
*@value: the string env var value
*
*Return: always 0
*
*/
int _setenv(my_info_t *info, char *var, char *value)
{
	char *buf = NULL;
	my_list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_my_strlen(var) + _my_strlen(value) + 2);
	if (!buf)
		return (1);
	_my_strcpy(buf, var);
	_my_strcat(buf, "=");
	_my_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = my_starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
