#include "./include/minishell.h"

char	*get_cmd_path(char *cmd, char *path)
{
	struct stat	sb;
	char		*rv_cmd;

	while (*path)
	{
		rv_cmd = ft_strjoin_free(ft_strjoin_free(ft_strndup(path,
						ft_strichr(path, ':')), "/"), cmd);
		if (!rv_cmd)
			allocat_error();
		if (stat(rv_cmd, &sb) >= 0)
			return (rv_cmd);
		free(rv_cmd);
		if (ft_strichr(path, ':') >= 0)
			path += ft_strichr(path, ':') + 1;
		else
			path += ft_strlen(path);
	}
	if (stat(cmd, &sb) >= 0)
		return (cmd);
	return (NULL);
}

int	is_cmd(char	*str)
{
	char	*path;
	char	*cmd_path;

	path = get_value_n("PATH", 4);
	cmd_path = get_cmd_path(str, path);
	free(path);
	if (cmd_path)
	{
		free(cmd_path);
		if (errno == ENOENT)
			return (0);
	}
	return (1);
}
