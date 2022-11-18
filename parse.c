#include "shell.h"

/**
  * parse_cmd - parse line in input
  * @input: user input to parse
  * Return: array of char (parsed): simple shell
  */
/*char **parse_cmd(char *input)
{
	char **tokens;
	char *token;
	int i, buffsize = BUFSIZ;

	if (input == NULL)
		return (NULL);

	tokens = malloc(sizeof(char *) * buffsize);
	if (!tokens)
	{
		perror("hsh");
		return (NULL);
	}
	tokens = _strtok(input, "\n ");
	for (i = 0; tokens; i++)
	{
		tokens[i] = token;
		token = _strtok(NULL, "\n ");
	}
	tokens[i] = NULL;

	return (tokens);
}*/

int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);

/**
  * is_cmd - determines if a file is an executable command
  * @info: the info struct
  * @path: path to the file
  * Return: 1 if succesful, 0 otherwise
  */
int is_cmd(info_t *info, char *path) 
{
	struct stat st;
	(void) info;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
  * dup_chars - duplicates characters
  * @pathstr: the path string
  * @start: start index
  * @stop: stop index
  * Return: pointer to new buffer
  */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
  * find_path - finds this cmd in the PATH string
  * @info: the info struct
  * @pathstr: the PATH string
  * @cmd: the cmd to find
  * Return: full path of cmd if found, otherwise NULL
  */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
