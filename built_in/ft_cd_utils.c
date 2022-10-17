#include "../include/minishell.h"

t_cd	*ft_init_cd_info(int pipe_cnt, char *arg)
{
	t_cd	*info;

	info = (t_cd *)malloc(sizeof(t_cd));
	if (!info)
		exit(1);
	info->cwd = getcwd(NULL, 0);
	info->pwd = get_env("PWD");
	info->pipe_cnt = pipe_cnt;
	info->path = arg;
	return (info);
}

void	ft_check_rv(t_cd *info)
{
	if (info->rv == 0)
	{
			free(info->cwd);
			info->cwd = getcwd(NULL, 0);
			ft_update_pwd(info->cwd);
			free(info->cwd);
			ft_update_oldpwd(info->pwd);
			free(info->pwd);
			set_exit_code(0);
			if (info->pipe_cnt)
				exit(0);
			return ;
	}
	else
	{
		chdir(info->cwd);
		free(info->cwd);
		free(info->pwd);
		printf("%s: cd: %s: No such file or directory\n", SHELL, info->path);
		set_exit_code(1);
		if (info->pipe_cnt)
			exit(1);
		return ;
	}
}

void	ft_cd_home(int pipe_cnt)
{
	char	*home;
	char	*pwd;

	pwd = get_env("PWD");
	home = get_env("HOME");
	if (!*home)
	{
		printf("%s: cd: HOME not set\n", SHELL);
		set_exit_code(1);
		if (pipe_cnt)
			exit(1);
	}
	else
	{
		chdir(home);
		ft_update_pwd(home);
		ft_update_oldpwd(pwd);
		free(pwd);
		free(home);
		set_exit_code(0);
		if (pipe_cnt)
			exit(1);
	}
}

void	ft_update_oldpwd(char *old_pwd)
{
	t_envlst	*tmp;

	if (!old_pwd)
		return ;
	tmp = g_info->envlst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(old_pwd);
			return ;
		}
		tmp = tmp->next;
	}
	if (g_info->oldpwd_flag == 0)
	{
		ft_envlst_add_back(ft_envlst_new("OLDPWD", old_pwd));
		g_info->oldpwd_flag = 1;
	}
}

void	ft_update_pwd(char *pwd)
{
	t_envlst	*tmp;

	if (!pwd)
		return ;
	tmp = g_info->envlst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(pwd);
			return ;
		}
		tmp = tmp->next;
	}
}
