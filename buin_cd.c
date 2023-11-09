/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buin_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:26:10 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/08 00:36:44 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	go_to(t_sh *sh, char *cs)
{
	char	*dir;
	int		dd;

	if (cs[0] == 0)
		return (0);
	if (cs[0] == '/')
		dir = ft_strdup(cs);
	else
	{
		dir = sjoin(sh->pwd, "/");
		dir = sjoin_f1(dir, cs);
	}
	dd = chdir(dir);
	if (dd)
	{
		free(dir);
		perror("cd");
		g_exit_code = 1;
		return (1);
	}
	free(sh->pwd);
	getcwd(dir, ft_strlen(dir));
	sh->pwd = ft_strdup(dir);
	free(dir);
	return (0);
}

void	run_cd(t_sh *sh, char **cs)
{
	char	*tmp;

	if (cs[1] && cs[2])
	{
		f_print(2, "cd: string not in pwd: %s\n", cs[1]);
		g_exit_code = 1;
		return ;
	}
	tmp = ft_strdup(sh->pwd);
	if (!cs[1] || !cs[1][0])
	{
		go_to(sh, sh->home);
	}
	else
	{
		if (go_to(sh, cs[1]))
		{
			free(tmp);
			return ;
		}
	}
	free(sh->odpwd);
	sh->odpwd = tmp;
	set_env_r(sh);
}
