/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buin_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 10:30:06 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/09 00:47:33 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	env_delete(t_sh *sh, int i)
{
	int	j;

	j = i;
	free(sh->env[i]);
	while (sh->env[j + 1])
	{
		sh->env[j] = sh->env[j + 1];
		j++;
	}
	sh->env[j] = 0;
}

void	env_append(t_sh *sh, char *cs)
{
	char	**re;
	int		l;
	int		i;

	i = find(sh->env, cs);
	if (i >= 0)
	{
		free(sh->env[i]);
		sh->env[i] = ft_strdup(cs);
		return ;
	}
	l = 0;
	while (sh->env[l])
		l++;
	re = malloc((l + 2) * sizeof(char *));
	if (!re)
		return ;
	i = -1;
	while (++i < l - 1)
		re[i] = sh->env[i];
	re[l - 1] = ft_strdup(cs);
	re[l] = sh->env[l - 1];
	re[l + 1] = 0;
	free(sh->env);
	sh->env = re;
}

void	run_env(t_sh *sh, char **cs)
{
	int	i;

	if (cs[1])
		return ;
	i = 0;
	while (sh->env[i])
	{
		f_print(1, "%s\n", sh->env[i]);
		i++;
	}
	g_exit_code = 0;
}
