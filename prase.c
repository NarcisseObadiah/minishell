/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prase.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 05:54:32 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/08 01:43:08 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	isin_quo(char c, int *in_quo)
{
	if (c == '\'')
	{
		if (*in_quo == 0)
			*in_quo = 1;
		else if (*in_quo == 1)
			*in_quo = 0;
	}
	else if (c == '"')
	{
		if (*in_quo == 0)
			*in_quo = 2;
		else if (*in_quo == 2)
			*in_quo = 0;
	}
}

char	*prase_each(t_sh *sh, char *c, int *j)
{
	int		i;
	int		in_quo;
	char	*re;

	re = malloc(1024);
	i = -1;
	in_quo = 0;
	while (c[++i])
	{
		if (c[i] == '\'' || c[i] == '"')
		{
			write_quo(c[i], re, j, in_quo);
			isin_quo(c[i], &in_quo);
		}
		else if (c[i] == '$' && in_quo != 1)
			i += write_dolor(&c[i + 1], sh, re, j);
		else
			re[(*j)++] = c[i];
	}
	re[*j] = 0;
	re = ft_sdupf(re);
	return (re);
}

char	**prase(t_sh *sh, char **cs)
{
	int		i;
	int		j;
	char	**re;

	j = 0;
	i = 0;
	while (cs[i])
		i++;
	re = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (cs[i])
	{
		j = 0;
		re[i] = prase_each(sh, cs[i], &j);
		i++;
	}
	re[i] = 0;
	return (re);
}
