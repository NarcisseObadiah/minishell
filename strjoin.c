/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 13:58:01 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/07 18:12:29 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sjoin(char const *s1, char const *s2)
{
	char			*re;
	size_t			j;
	size_t			tot;

	tot = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	re = malloc(tot + 1);
	if (!re)
		return (0);
	j = 0;
	while (s1[j])
	{
		re[j] = s1[j];
		j++;
	}
	tot = 0;
	while (s2[tot])
	{
		re[j] = s2[tot];
		tot++;
		j++;
	}
	re[j] = 0;
	return (re);
}

char	*sjoin_f1(char const *s1, char const *s2)
{
	char			*re;
	size_t			j;
	size_t			tot;

	tot = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	re = malloc(tot + 1);
	if (!re)
		return (0);
	j = 0;
	while (s1[j])
	{
		re[j] = s1[j];
		j++;
	}
	tot = 0;
	while (s2[tot])
	{
		re[j] = s2[tot];
		tot++;
		j++;
	}
	re[j] = 0;
	free((void *)s1);
	return (re);
}

char	*sjoin_f2(char const *s1, char const *s2)
{
	char			*re;
	size_t			j;
	size_t			tot;

	tot = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	re = malloc(tot + 1);
	if (!re)
		return (0);
	j = 0;
	while (s1[j])
	{
		re[j] = s1[j];
		j++;
	}
	tot = 0;
	while (s2[tot])
	{
		re[j] = s2[tot];
		tot++;
		j++;
	}
	re[j] = 0;
	free((void *)s2);
	return (re);
}
