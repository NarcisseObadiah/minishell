/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:54:15 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/08 22:17:23 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_all(char **cs)
{
	int	i;

	if (!cs)
		return ;
	i = 0;
	while (cs[i])
	{
		free(cs[i]);
		i++;
	}
	free(cs);
}

void	free_sh(t_sh *sh)
{
	free_all(sh->env);
	free_all(sh->evpth);
	free(sh->odpwd);
	free(sh->pwd);
	free(sh->user);
}
