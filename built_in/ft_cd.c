#include "../include/minishell.h"

static void	ft_update_oldpwd(char *old_pwd);
static void	ft_update_pwd(char *pwd);

void	ft_cd(char *path)
{
	int		rv;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (*path == '~')
	{
		chdir("/");
		if (*(path + 1))
			rv = chdir(*(path + 1));
	}
	else
		rv = chdir(path);
	if (rv == 0)
	{
		ft_update_oldpwd(cwd);
		ft_update_pwd(getenv("PWD"));
	}
	else
	{
		chdir(cwd);
		printf("minishell: cd: %s: No such file or directory\n", path);
	}
}

static void	ft_update_oldpwd(char *old_pwd)
{
	t_envlst	*tmp;

	tmp = g_envlst;
	while (tmp)
	{
		if (tmp->key == "OLDPWD")
		{
			tmp->value = old_pwd;
			return ;
		}
		tmp = tmp->next;
	}
	ft_lst_add_back(ft_lst_new("OLDPWD", old_pwd));
}

static void	ft_update_pwd(char *pwd)
{
	t_envlst	*tmp;

	tmp = g_envlst;
	while (tmp)
	{
		if (tmp->key == "PWD")
		{
			tmp->value = pwd;
			return ;
		}
		tmp = tmp->next;
	}
	ft_lst_add_back(ft_lst_new("PWD", pwd));
}