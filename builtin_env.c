#include "shell.h"

int _env(char **args, char __attribute__((unused)) **front);
int _setenv(char **args, char __attribute__((unused)) **front);
int _unsetenv(char **args, char __attribute__((unused)) **front);

/**
  * _env - prints the current environment
  * @args: an array of arguments passed to the shell.
  * @front: a double pointer to the beginning of the args.
  * Return: -1 if an error, otherwise 0.
  * Note, prints one 'variable' = 'value', per line.
  */
int _env(char **args, char __attribute__((unused)) **front)
{
	int index;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}
	(void)args;
	return (0);
}

/**
  * _setenv - changes or adds an environmental variable to the PATH
  * @args: an array of arguments passed to the shell.
  * @front: a double pointer to the beginning of the args.
  * Return: -1 if an error, otherwise 0.
  * Note, args[1] is the name of the new or existing PATH variable.
  * args[2] is the value to set the new or changed variable to.
  */
int _setenv(char **args, char __attribute__((unused)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (create_error(args, -1));

	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;
	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (create_error(args, -1));
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;

	return (0);
}








































