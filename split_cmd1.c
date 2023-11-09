/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:00:10 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/09 10:38:59 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	each_cmd(char ***css, char **cs, int *inx, int *i)
{
	if (pip_redir(cs[inx[i[0]]]) == 'p')
	{
		css[i[1]++] = get_cmd(cs, inx, i[0] - 1);
		css[i[1]] = malloc(2 * sizeof(char **));
		if (!css[i[1]])
			return ;
		css[i[1]][0] = ft_strdup(cs[inx[i[0]]]);
		css[i[1]++][1] = 0;
	}
	else if (pip_redir(cs[inx[i[0]]]))
	{
		css[i[1]++] = get_cmd(cs, inx, i[0] - 1);
		css[i[1]] = malloc(3 * sizeof(char **));
		if (!css[i[1]])
			return ;
		css[i[1]][0] = ft_strdup(cs[inx[i[0]]]);
		css[i[1]][1] = ft_strdup(cs[inx[i[0]] + 1]);
		css[i[1]++][2] = 0;
	}
}

void	vaild(char **cs)
{
	int	i;

	if (pip_redir(cs[0]) == 'p')
	{
		f_print(2, "minishell: syntax error near unexpected token `|'\n");
		exit(258);
	}
	i = 0;
	while (cs[++i])
	{
		if (pip_redir(cs[i - 1]) && pip_redir(cs[i]))
		{
			f_print(2, "minishell: syntax error near ");
			f_print(2, "unexpected token `%s'\n", cs[i]);
			exit(258);
		}
	}
	if (pip_redir(cs[i - 1]))
	{
		f_print(2, "minishell: syntax error near ");
		f_print(2, "unexpected token `newline'\n");
		exit(258);
	}
}

// void	check(char ***css)
// {
// 	if (pip_redir(css[0]) == 'p')
// }
char	***reload(char ***css)
{
	char	***re;
	int		i;
	int		j;

	i = 0;
	while (css[i])
		i++;
	re = malloc((i + 1) * sizeof(char **));
	i = -1;
	j = 0;
	while (css[++i])
	{
		if (css[i][0])
			re[j++] = css[i];
	}
	re[j] = 0;
	free(css);
	return (re);
}
