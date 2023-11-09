/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 03:31:37 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/09 16:38:56 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_dir(t_sh *shell)
{
	char	*a;
	int		i;

	i = 0;
	a = sjoin_f1(ft_strdup(shell->user), "@minishell ");
	i = ft_strlen(shell->pwd);
	while (shell->pwd[i] != '/')
		i--;
	if (ft_strncmp(shell->pwd, shell->home, 2147483647))
	{
		if (ft_strlen(shell->pwd) < ft_strlen(shell->home))
			a = sjoin_f1(a, &(shell->pwd[i]));
		else
			a = sjoin_f1(a, &(shell->pwd[i + 1]));
	}
	else
		a = sjoin_f1(a, "~");
	a = sjoin_f1(a, " % ");
	return (a);
}

void	run_shell(t_sh *shell)
{
	char	*p;
	char	*cmd;
	char	**cs;

	while (shell->runing)
	{
		set_signal_b();
		p = get_dir(shell);
		cmd = readline(p);
		free(p);
		set_signal_a();
		if (!cmd)
			break ;
		if (cmd[0])
			add_history(cmd);
		cs = ft_split(cmd, ' ');
		exe_all(shell, prase(shell, cs));
		set_envpth(shell);
		free(cmd);
		free_all(cs);
	}
	printf("\n[Process completed]\n\n");
}

void	all(char **env)
{
	t_sh	sh;

	sh.env = env;
	set_env(&sh);
	run_shell(&sh);
	free_sh(&sh);
}

int	main(int argi, char **argv, char **env)
{
	argi = 0;
	argv = 0;
	all(env);
	system("leaks minishell");
	return (g_exit_code);
}
