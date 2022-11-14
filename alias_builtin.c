#include "shell.h"

int _alias(char **args, char __attribute__((unused)) **front);
void set_alias(char *var_name, cahr *value);
void print_alias(alias_t *alias);

/**
  * _alias - builtin command that either prints all aliases,
  * specific aliases, or sets an alias.
  * @args: an array of arguments.
  * @front: a double pointer to the beginning of the args.
  * Return: -1 if is an error, otherwise 0.
  */
int _alias(char **args, char __attribute__((unused)) **front)
{
	alias_t *temp = aliases;
	int i, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		value = _strchr(args[i], '=');
		if (!value)
		{
			while (temp)
			{
				if (_strcmp(args[i], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = create_error(args + i, 1);
		}
		else
			set_alias(args[i], value);
	}
	return (ret);
}


/**
  * set_alias - will either set an existing alias 'name' with a new value,
  * 'value' or creates a new aliaswith 'name' and 'value'
  * @var_name: name of the alias
  * @value: value of the alias. First character is a '='
  */
void set_alias(char *var_name, cahr *value)
{
	alias_t *temp = aliases;
	int length, j, k;
	char *new_value;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if(!new_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, new_value);
}


















