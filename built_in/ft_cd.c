#include "../include/minishell.h"

void	ft_cd(char **arg, int pipe_cnt)
{
	t_cd	*info;

	if (!arg[1])
		ft_cd_home(pipe_cnt);
	else
	{
		info = ft_init_cd_info(pipe_cnt, arg[1]);
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
}

