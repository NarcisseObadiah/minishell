/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prase_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 02:39:42 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/08 00:39:54 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	write_quo(char c, char *re, int *j, int in_quo)
{
	if (in_quo == 0)
		return ;
	if (in_quo == 1 && c == '"')
		re[(*j)++] = c;
	else if (in_quo == 2 && c == '\'')
		re[(*j)++] = c;
}

void	write_exit(t_sh *sh, char *re, int *j)
{
	int	exit;

	(void)sh;
	exit = g_exit_code;
	if (exit / 100)
		re[(*j)++] = exit / 100 + 48;
	if (exit / 100 || exit % 100 / 10)
		re[(*j)++] = exit % 100 / 10 + 48;
	exit = exit % 10;
	re[(*j)++] = exit + 48;
}

int	write_dolor(char *c, t_sh *sh, char *re, int *j)
{
	int		len;
	char	tmp;
	int		f;
	int		i;

	if (c[0] == '?')
	{
		write_exit(sh, re, j);
		return (1);
	}
	len = 1;
	while (is_aphnum(c[len]))
		len++;
	tmp = c[len];
	c[len] = '=';
	f = find(sh->env, c);
	c[len] = tmp;
	i = len + 1;
	if (f >= 0)
	{
		while (sh->env[f][i])
			re[(*j)++] = sh->env[f][i++];
	}
	return (len);
}
