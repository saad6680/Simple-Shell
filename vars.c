#include "modified_shell.h"

/**
 * is_command_chain - test if current char in buffer is a command chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if command chain delimiter, 0 otherwise
 */
int mod_is_command_chain(modified_info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
	buf[j] = 0;
	j++;
	info->cmd_buf_type = MOD_CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
	buf[j] = 0;
	j++;
	info->cmd_buf_type = MOD_CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
	buf[j] = 0; /* replace semicolon with null */
	info->cmd_buf_type = MOD_CMD_CHAIN;
	}
	else
	return (0);
	*p = j;
	return (1);
}

/**
 * mod_check_command_chain - checks if we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void mod_check_command_chain(modified_info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == MOD_CMD_AND)
	{
	if (info->status)
	{
	buf[i] = 0;
	j = len;
	}
	}
	if (info->cmd_buf_type == MOD_CMD_OR)
	{
	if (!info->status)
	{
	buf[i] = 0;
	j = len;
	}
	}

	*p = j;
}

/**
 * mod_replace_alias - replaces an alias in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int mod_replace_alias(modified_info_t *info)
{
	int i;
	modified_list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
	node = mod_node_starts_with(info->alias, info->argv[0], '=');
	if (!node)
	return (0);
	free(info->argv[0]);
	p = mod_strchr(node->str, '=');
	if (!p)
	return (0);
	p = mod_strdup(p + 1);
	if (!p)
	return (0);
	info->argv[0] = p;
	}
	return (1);
}

/**
 * mod_replace_variables - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int mod_replace_variables(modified_info_t *info)
{
	int i = 0;
	modified_list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
	if (info->argv[i][0] != '$' || !info->argv[i][1])
	continue;

	if (!mod_strcmp(info->argv[i], "$?"))
	{
	mod_replace_string(&(info->argv[i]),
	mod_strdup(mod_convert_number(info->status, 10, 0)));
	continue;
	}
	if (!mod_strcmp(info->argv[i], "$$"))
	{
	mod_replace_string(&(info->argv[i]),
	mod_strdup(mod_convert_number(getpid(), 10, 0)));
	continue;
	}
	node = mod_node_starts_with(info->env, &info->argv[i][1], '=');
	if (node)
	{
	mod_replace_string(&(info->argv[i]),
	mod_strdup(mod_strchr(node->str, '=') + 1));
	continue;
	}
	mod_replace_string(&info->argv[i], mod_strdup(""));

	}
	return (0);
}

/**
 * mod_replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int mod_replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
