#include "shell.h"
/**
*_my_exit - exits the shell
*@info: structure containing potential arguments. used to maintain
*
*Return: exits with given exit status
*
*/
int _my_exit(my_info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = my_erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			my_print_error(info, "Illegal number: ");
			_my_eputs(info->argv[1]);
			_my_eputchar('\n');
			return (1);
		}
		info->err_num = my_erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
*_my_cd - changes current directory of the process
*@info: structure containing potential arguments. used to maintain
*
*Return: Always 0
*
*/
int _my_cd(my_info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_my_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _my_getenv(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _my_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_my_strcmp(info->argv[1], "-") == 0)
	{
		if (!_my_getenv(info, "OLDPWD="))
		{
			_my_puts(s);
			_my_putchar('\n');
			return (1);
		}
		_my_puts(_my_getenv(info, "OLDPWD=")), _my_putchar('\n');
		chdir_ret = chdir((dir = _my_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		my_print_error(info, "can't cd to ");
		_my_eputs(info->argv[1]), _my_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _my_getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
*_my_help - changes the current directory of the process
*@info: structure containing potential arguments. used to maintain
*
*Return: Always 0
*
*/
int _my_help(my_info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_my_puts("help call works. Function not yet implemented \n");
	if (0)
		_my_puts(*arg_array);
	return (0);
}
