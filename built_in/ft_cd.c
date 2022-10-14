#include "minishell.h"

static void	ft_update_oldpwd(char *old_pwd);
static void	ft_update_pwd(char *pwd);
static void	ft_cd_home(int pipe_cnt);
static void	ft_check_rv(t_cd *info);

void	ft_cd(char **arg, int pipe_cnt)
{
	t_cd	*info;

	if (!arg[1])
		ft_cd_home(pipe_cnt);
	info->cwd = getcwd(NULL, 0);
	info->pwd = get_env("PWD");
	info->pipe_cnt = pipe_cnt;
	info->path = arg[1];
	if (arg[1][0] == '~')
	{
		info->rv = chdir("/");
		info->rv = chdir(g_info->home);
		if (arg[1][1] && arg[1][1] == '/' && arg[1][2])
			info->rv = chdir(&arg[1][2]);
		else if (arg[1][1] && arg[1][1] != '/')
			info->rv = -1;
	}
	else
		info->rv = chdir(arg[1]);
	ft_check_rv(info);
}

static void	ft_check_rv(t_cd *info)
{
	if (info->rv == 0)
	{
		if (info->pipe_cnt)
		{
			chdir(info->cwd);
			free(info->cwd);
			free(info->pwd);
		}
		else
		{
			free(info->cwd);
			info->cwd = getcwd(NULL, 0);
			ft_update_pwd(info->cwd);
			free(info->cwd);
			ft_update_oldpwd(info->pwd);
			free(info->pwd);
			exit(0);
		}
	}
	else
	{
		chdir(info->cwd);
		free(info->cwd);
		free(info->pwd);
		printf("%s: cd: %s: No such file or directory\n", SHELL, info->path);
		exit(1);
	}
}

static void	ft_cd_home(int pipe_cnt)
{
	char	*home;
	char	*pwd;

	pwd = get_env("PWD");
	home = get_env("HOME");
	if (!home)
		printf("%s: cd: HOME not set", SHELL);
	else
	{
		if (!pipe_cnt)
		{
			chdir(home);
			ft_update_pwd(home);
			ft_update_oldpwd(pwd);
			free(pwd);
			free(home);
		}
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
