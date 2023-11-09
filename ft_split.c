/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 00:50:28 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/05 22:04:36 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t	skip_quo(char *dup, size_t i)
{
	if (dup[i] == 39)
	{
		i++;
		while (dup[i] && dup[i] != 39)
			i++;
	}
	else if (dup[i] == 34)
	{
		i++;
		while (dup[i] && dup[i] != 34)
			i++;
	}
	if (dup[i])
		return (i);
	else
		return (i - 1);
}

size_t	cut(char *dup, char set)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (dup[0] == 0)
		return (0);
	if (dup[0] != set)
		count++;
	while (dup[i])
	{
		if (dup[i] == 39 || dup[i] == 34)
			i = skip_quo(dup, i);
		if (dup[i] == set)
		{
			dup[i] = 0;
			if (dup[i + 1] && dup[i + 1] != set)
				count++;
		}
		i++;
	}
	return (count);
}

int	w_split(char **re, char *dup, size_t len)
{
	size_t	i;
	int		tot;

	i = 0;
	tot = 0;
	if (dup[0])
	{
		re[tot] = ft_strdup((char *)dup);
		if (!re[tot])
			return (tot);
		tot++;
	}
	while (i + 1 < len)
	{
		if ((dup[i] == 0) && dup[i + 1])
		{
			re[tot] = ft_strdup((char *)dup + i + 1);
			if (!re[tot])
				return (tot);
			tot++;
		}
		i++;
	}
	re[tot] = 0;
	return (-1);
}

void	free_re(char **re, int tot)
{
	while (tot > 0)
	{
		tot--;
		free(re[tot]);
	}
	free(re);
}

char	**ft_split(char const *s, char c)
{
	char		*dup;
	char		**re;
	size_t		tot;
	int			i;

	dup = ft_strdup((char *)s);
	if (!dup)
		return (0);
	tot = cut(dup, c);
	re = (char **)malloc((tot + 1) * sizeof(char *));
	if (!re)
	{
		free(dup);
		return (0);
	}
	i = w_split(re, dup, ft_strlen(s));
	if (i >= 0)
	{
		free_re(re, i);
		re = 0;
	}
	free(dup);
	return (re);
}

// int main() {
// 	char **sp = ft_split("a sk '  lf\"hal 's\" fk", ' ');
// 	int i = 0;
// 	while (sp[i]) {
// 		printf("%s|\n", sp[i]);
// 		i++;
// 	}
// 	return 0;
// }