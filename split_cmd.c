/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 06:31:47 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/09 10:58:41 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	pip_redir(char *s)
{
	if (s[0] == '|' && s[1] == 0)
		return ('p');
	if (s[0] == '<' && s[1] == 0)
		return ('i');
	if (s[0] == '>' && s[1] == 0)
		return ('o');
	if (s[0] == '<' && s[1] == '<' && s[2] == 0)
		return ('d');
	if (s[0] == '>' && s[1] == '>' && s[2] == 0)
		return ('a');
	return (0);
}

int	count_cmd(char **cs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cs[i])
	{
		if (pip_redir(cs[i]))
		{
			j++;
			if (pip_redir(cs[i]) != 'p')
				j++;
		}
		i++;
	}
	return (j);
}

int	*split_pos(char **cs)
{
	int	i;
	int	j;
	int	*inx;

	i = 0;
	j = count_cmd(cs);
	inx = malloc((j + 3) * sizeof(int));
	if (!inx)
		return (0);
	inx[0] = -1 - 2 * j;
	i = -1;
	j = 1;
	while (cs[++i])
	{
		if (pip_redir(cs[i]) == 'p')
			inx[j++] = i;
		else if (pip_redir(cs[i]))
		{
			inx[j++] = i++;
			inx[j++] = i;
		}
	}
	inx[j++] = i;
	inx[j] = -1;
	return (inx);
}

char	**get_cmd(char **cs, int *inx, int i)
{
	char	**re;
	int		j;
	int		k;

	j = inx[i] + 1;
	if (i == 0)
		j = 0;
	re = malloc((inx[i + 1] - inx[i] + 1) * sizeof(char *));
	if (!re)
		return (0);
	k = 0;
	while (j < inx[i + 1])
	{
		re[k] = cs[j];
		k++;
		j++;
	}
	re[k] = 0;
	return (re);
}

// void	prnt(char ***css)
// {
// 	int i = 0;
// 	int j = 0;
// 	while (css[i])
// 	{
// 		j = 0;
// 		while (css[i][j])
// 		{
// 			printf("-%s-", css[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

char	***split_cmd(char **cs)
{
	int		i[2];
	int		*inx;
	char	***css;

	i[0] = 1;
	i[1] = 0;
	vaild(cs);
	inx = split_pos(cs);
	if (!inx)
		return (0);
	css = malloc(2 * (-inx[0] + 2) * sizeof(char **));
	if (!css)
		return (0);
	while (inx[i[0] + 1] >= 0)
	{
		each_cmd(css, cs, inx, i);
		i[0]++;
	}
	css[i[1]++] = get_cmd(cs, inx, i[0] - 1);
	css[i[1]] = 0;
	css = reload(css);
	free(inx);
	return (css);
}
