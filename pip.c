/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 04:21:16 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/09 18:34:49 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	run_one(t_sh *sh, char **cs)
{
	char	*pth;

	if (pip_redir(cs[0]))
		exit(0);
	pth = get_pth(sh->evpth, cs[0]);
	if (!pth)
	{
		if (cs[0][0] == '.' || cs[0][0] == '/')
			f_print(2, "minishell: %s: No such file or directory\n", cs[0]);
		else
			f_print(2, "minishell: %s: command not found\n", cs[0]);
		exit(127);
	}
	execve(pth, cs, sh->env);
	perror("minishell");
	exit(1);
}

void	run_pip(t_sh *sh, char **cs)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		f_print(2, "Error creating pipe\n");
	pid = fork();
	if (pid == -1)
		f_print(2, "Error creating process\n");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		exe_cmd(sh, cs);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	run_set(t_sh *sh, char ***css, int i)
{
	if (pip_redir(css[i][0]) == 'p')
		run_pip(sh, css[i - 1]);
	else if (pip_redir(css[i][0]))
		redir(sh, css, &i);
	if (!css[i + 1])
	{
		exe_cmd(sh, css[i]);
	}
}

void	run_row(t_sh *sh, char **cs)
{
	char	***css;
	int		i;
	pid_t	main;

	main = fork();
	if (main == 0)
	{
		sh->child = 1;
		css = split_cmd(cs);
		i = -1;
		while (css[++i])
		{
			run_set(sh, css, i);
		}
	}
	else
	{
		waitpid(main, &i, 0);
		g_exit_code = i / 256;
		if (i == 512)
			g_exit_code = 258;
	}
}
