/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 05:10:20 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/09 12:04:47 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	redir_o(t_sh *sh, char ***css, int *i)
{
	int		out;
	char	type;

	(void)sh;
	type = pip_redir(css[*i][0]);
	if (type == 'o')
	{
		out = open(css[*i][1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	}
	else
	{
		out = open(css[*i][1], O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	}
	if (out == -1)
	{
		perror("minishell");
		g_exit_code = 1;
		return ;
	}
	dup2(out, 1);
	exe_cmd(sh, css[*i - 1]);
	close(out);
}

void	redir_i(t_sh *sh, char ***css, int *i)
{
	int		in;
	char	type;

	(void)sh;
	in = 0;
	type = pip_redir(css[*i][0]);
	if (type == 'i')
	{
		in = open(css[*i][1], O_RDONLY, S_IRWXU);
	}
	if (in == -1)
	{
		perror("minishell");
		g_exit_code = 1;
		return ;
	}
	dup2(in, 0);
}

void	send_line(char *cs, int fd)
{
	char	*line;
	char	*endl;

	while (1)
	{
		line = readline("heredoc> ");
		endl = sjoin(line, "\n");
		write(fd, endl, ft_strlen(endl));
		free(endl);
		if (ft_strncmp(line, cs, 2147483647) == 0)
		{
			free(line);
			exit(0);
		}
		free(line);
	}
}

void	hir_doc(char ***css, int *i)
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
		send_line(css[*i][1], fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		wait(NULL);
	}
}

void	redir(t_sh *sh, char ***css, int *i)
{
	char	type;

	type = pip_redir(css[*i][0]);
	if (type == 'o' || type == 'a')
		redir_o(sh, css, i);
	else if (type == 'i')
		redir_i(sh, css, i);
	else
		hir_doc(css, i);
}
