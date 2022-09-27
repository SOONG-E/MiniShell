#include "../include/minishell.h"

static void	ft_update_oldpwd(char *old_pwd);
static void	ft_update_pwd(char *pwd);

void	ft_cd(char *path)
{
	int		rv;
	char	*cwd;
	char	*pwd;

	cwd = getcwd(NULL, 0);
	pwd = getenv("PWD");
	if (*path == '~')
	{
		rv = chdir("/");
		rv = chdir("/Users/minsukan/");
		printf("%s\n", path + 1);
		if (*(path + 1))
			rv = chdir(path + 1);
	}
	else
		rv = chdir(path);
	if (rv == 0)
	{
		ft_update_oldpwd(pwd);
		ft_update_pwd(pwd);
		free(cwd);
	}
	else
	{
		chdir(cwd);
		free(cwd);
		printf("minishell: cd: %s: No such file or directory\n", path);
	}
}

static void	ft_update_oldpwd(char *old_pwd)
{
	t_envlst	*tmp;

	if (!old_pwd)
		return ;
	tmp = g_envlst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			tmp->value = old_pwd;
			return ;
		}
		tmp = tmp->next;
	}
	// if (처음 만들어지는 거라면)
	// 	ft_lst_add_back(ft_lst_new("OLDPWD", old_pwd));
}

static void	ft_update_pwd(char *pwd)
{
	t_envlst	*tmp;

	if (!pwd)
		return ;
	tmp = g_envlst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			tmp->value = pwd;
			return ;
		}
		tmp = tmp->next;
	}
}

