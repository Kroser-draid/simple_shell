#include "shell.h"

/**
*my_shell - main shell loop
*@info: the parameter & return info struct
*@av: the argument vector from main()
*
*Return: 0 on success, 1 on error, or error code
*
*/
int my_shell(my_info_t *info, char **av)
{
	ssize_t r = 0;
	int my_builtin_ret = 0;

	while (r != -1 && my_builtin_ret != -2)
	{
		clear_info(info);
		if (my_interactive(info))
			_my_puts("$ ");
		_my_eputchar(MY_BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			my_builtin_ret = find_builtin(info);
			if (my_builtin_ret == -1)
				find_cmd(info);
		}
		else if (my_interactive(info))
			_my_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!my_interactive(info) && info->status)
		exit(info->status);
	if (my_builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (my_builtin_ret);
}

/**
* find_builtin - find a my_builtin command
* @info: the parameter & return info struct
*
* Return: -1 if my_builtin not found,
*			0 if my_builtin executed successfully,
*			1 if my_builtin found but not successful,
*			-2 if my_builtin signals exit()
*/
int find_builtin(my_info_t *info)
{
	int i, built_in_ret = -1;
	my_builtin_table my_builtintbl[] = {
		{"exit", _my_exit},
		{"env", _my_env},
		{"help", _my_help},
		{"history", _my_history},
		{"setenv", _my_setenv},
		{"unsetenv", _my_unsetenv},
		{"cd", _my_cd},
		{"alias", _my_alias},
		{NULL, NULL}
	};

	for (i = 0; my_builtintbl[i].type; i++)
		if (_my_strcmp(info->argv[0], my_builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = my_builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
*find_cmd - finds a command in PATH
*@info: the parameter & return info struct
*
*Return: void
*
*/
void find_cmd(my_info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!my_is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_my_path(info, _my_getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((my_interactive(info) || _my_getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			my_print_error(info, "not found\n");
		}
	}
}

/**
*fork_cmd - forks an exec thread to run cmd
*@info: the parameter & return info struct
*
*Return: void
*
*/
void fork_cmd(my_info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				my_print_error(info, "Permission denied\n");
		}
	}
}
