#include "../include/minishell.h"

static void	ft_update_oldpwd(char *old_pwd);
static void	ft_update_pwd(char *pwd);
static void	ft_cd_home(void);

void	ft_cd(char *path)
{
	int		rv;
	char	*cwd;
	char	*pwd;

	if (!path)
		ft_cd_home();
	cwd = getcwd(NULL, 0);
	pwd = getenv("PWD");
	if (*path == '~')
	{
		rv = chdir("/");
		rv = chdir("Users/minsukan");
		if (*(path + 1) == '/' && *(path + 2))
			rv = chdir(path + 2);
		else if (*(path + 1) != '/')
			rv = 1;
		else if (*(path + 1) == '/' && !*(path + 2))
			rv = 0;
	}
	else
		rv = chdir(path);
	if (rv == 0)
	{
		ft_update_pwd(pwd);
		ft_update_oldpwd(pwd);
		free(cwd);
	}
	else
	{
		chdir(cwd);
		free(cwd);
		printf("minishell: cd: %s: No such file or directory\n", path);
	}
}

static void	ft_cd_home(void)
{
	char	*home;
	char	*pwd;

	pwd = getenv("PWD");
	home = getenv("HOME");
	if (!home)
		printf("minishell: cd: HOME not set");
	else
	{
		chdir(home);
		ft_update_pwd(pwd);
		ft_update_oldpwd(pwd);
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

