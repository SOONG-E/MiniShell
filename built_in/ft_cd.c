#include "../include/minishell.h"

static void	ft_update_oldpwd(char *old_pwd);
static void	ft_update_pwd(char *pwd);
static void	ft_cd_home(void);
static int	ft_check_rv(char *path, char *cwd, char *pwd, int rv);

int	ft_cd(char *path)
{
	int		rv;
	char	*cwd;
	char	*pwd;

	if (!path)
		ft_cd_home();
	cwd = getcwd(NULL, 0);
	pwd = ft_get_env("PWD");
	if (path[0] == '~')
	{
		rv = chdir("/");
		rv = chdir(g_info->home);
		if (path[1] && path[1] == '/' && path[2])
			rv = chdir(path + 2);
		else if (path[1] && path[1] != '/')
			rv = -1;
	}
	else
		rv = chdir(path);
	return (ft_check_rv(path, cwd, pwd, rv));
}

static int	ft_check_rv(char *path, char *cwd, char *pwd, int rv)
{
	if (rv == 0)
	{
		free(cwd);
		cwd = getcwd(NULL, 0);
		ft_update_pwd(cwd);
		free(cwd);
		ft_update_oldpwd(pwd);
		free(pwd);
		return (1);
	}
	else
	{
		chdir(cwd);
		free(cwd);
		free(pwd);
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (0);
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
		ft_update_pwd(home);
		ft_update_oldpwd(pwd);
	}
}

static void	ft_update_oldpwd(char *old_pwd)
{
	t_envlst	*tmp;

	if (!old_pwd)
		return ;
	tmp = g_info->envlst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = old_pwd;
			return ;
		}
		tmp = tmp->next;
	}
	if (g_info->oldpwd_flag == 0)
	{
		ft_add_back_env(ft_new_env("OLDPWD", old_pwd));
		g_info->oldpwd_flag = 1;
	}
}

static void	ft_update_pwd(char *pwd)
{
	t_envlst	*tmp;

	if (!pwd)
		return ;
	tmp = g_info->envlst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
		{
			free(tmp->value);
			tmp->value = pwd;
			return ;
		}
		tmp = tmp->next;
	}
}

