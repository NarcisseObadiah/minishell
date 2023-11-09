/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buin_export1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:07:36 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/07 02:07:29 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	is_aphnum(char c)
{
	if (c == '_')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	valid_exp(char *s)
{
	int	i;

	if (s[0] == '=')
		return (1);
	i = -1;
	while (s[++i] && s[i] != '=')
	{
		if (is_aphnum(s[i]) == 0)
			return (1);
	}
	return (0);
}
