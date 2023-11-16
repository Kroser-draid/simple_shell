#include "shell.h"

/**
*_my_history - displays the history list, one command by line
*@info: structure containing potential arguments. used to maintain
*
*Return: always 0
*
*/
int _my_history(my_info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
*unset_alias - remove alias
*@info: parameter struct
*@str: the string alias
*
*Return: always 0 on success, 1 on error
*
*/
int unset_alias(my_info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _my_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
*set_alias - sets alias to string
*@info:parameter struct
*@str: the string alias
*
*Return: always 0 on success, 1 on error
*
*/
int set_alias(my_info_t *info, char *str)
{
	char *p;

	p = _my_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
*print_alias - prints an alias string
*@node: the alias node
*
*Return: Always 0 on success, 1 on error
*
*/
int print_alias(my_list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _my_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_my_putchar(*a);
		_my_putchar('\'');
		_my_puts(p + 1);
		_my_puts("'\n");
		return (0);
	}
	return (1);
}

/**
*_my_alias - mimics the alias my_builtin (man alias)
*@info: structure containing potential arguments. used to maintain
*
*Return: Always 0
*
*/
int _my_alias(my_info_t *info)
{
	int i = 0;
	char *p = NULL;
	my_list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _my_strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
