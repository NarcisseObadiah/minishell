/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buin_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 03:44:47 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/08 00:40:08 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	echo(char **cs)
{
	int	i;

	i = 1;
	while (cs[i])
	{
		if (i != 1)
			f_print(1, " ");
		f_print(1, "%s", cs[i]);
		i++;
	}
	f_print(1, "\n");
}

void	echo_n(char **cs)
{
	int	i;

	i = 2;
	while (cs[i])
	{
		if (i != 2)
			f_print(1, " ");
		f_print(1, "%s", cs[i]);
		i++;
	}
}

void	run_echo(t_sh *sh, char **cs)
{
	(void)sh;
	if (!cs[1])
		f_print(1, "\n");
	else if (ft_strncmp(cs[1], "-n", 3))
		echo(cs);
	else
		echo_n(cs);
	g_exit_code = 0;
}
