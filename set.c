/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 01:30:12 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/09 00:52:51 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	find(char **str, char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[len] != '=')
		len++;
	len++;
	while (str[i])
	{
		if (ft_strncmp(str[i], s, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	set_env(t_sh *shell)
{
	int		i;
	char	**re;

	i = 0;
	while (shell->env[i])
		i++;
	re = malloc((i + 1) * sizeof(char *));
	i = -1;
	while (shell->env[++i])
		re[i] = ft_strdup(shell->env[i]);
	shell->env = re;
	i = find(shell->env, "PWD=");
	shell->pwd = ft_strdup(shell->env[i] + 4);
	i = find(shell->env, "OLDPWD=");
	shell->odpwd = ft_strdup(shell->env[i] + 7);
	shell->user = ft_strdup(shell->env[find(shell->env, "USER=")] + 5);
	shell->home = shell->env[find(shell->env, "HOME=")] + 5;
	shell->evpth = ft_split(shell->env[find(shell->env, "PATH=")] + 5, ':');
	shell->runing = 1;
	shell->env[find(shell->env, "SHLVL=")][6]++;
	g_exit_code = 0;
}

/*
set env reverse
*/
void	set_env_r(t_sh *shell)
{
	int	i;

	i = find(shell->env, "PWD=");
	free(shell->env[i]);
	shell->env[i] = sjoin("PWD=", shell->pwd);
	i = find(shell->env, "OLDPWD=");
	free(shell->env[i]);
	shell->env[i] = sjoin("OLDPWD=", shell->odpwd);
}

void	set_envpth(t_sh *sh)
{
	if (sh->evpth)
		free_all(sh->evpth);
	if (find(sh->env, "PATH=") >= 0)
		sh->evpth = ft_split(sh->env[find(sh->env, "PATH=")] + 5, ':');
	else
		sh->evpth = 0;
}
