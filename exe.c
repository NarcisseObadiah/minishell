/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 03:58:57 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/09 17:33:52 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_pth(char **evpth, char *cs)
{
	char	*right_path;
	char	*cmd;
	int		i;

	right_path = 0;
	if (access(cs, F_OK | X_OK) == 0)
		return (ft_strdup(cs));
	cmd = sjoin("/", cs);
	i = -1;
	while (evpth && evpth[++i])
	{
		right_path = sjoin(evpth[i], cmd);
		if (access(right_path, F_OK | X_OK) == 0)
			break ;
		free(right_path);
		right_path = 0;
	}
	free(cmd);
	return (right_path);
}

void	run_exe(t_sh *sh, char **cs)
{
	char	*pth;
	pid_t	m_pid;
	int		exit_code;

	m_pid = fork();
	if (m_pid)
	{
		waitpid(m_pid, &exit_code, 0);
		g_exit_code = exit_code / 256;
	}
	else if (m_pid == 0)
	{
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
}

void	exe_cmd(t_sh *sh, char **cs)
{
	if (!cs[0])
		return ;
	if (ft_strncmp(cs[0], "cd", 3) == 0)
		run_cd(sh, cs);
	else if (ft_strncmp(cs[0], "echo", 5) == 0)
		run_echo(sh, cs);
	else if (ft_strncmp(cs[0], "pwd", 4) == 0)
		run_pwd(sh, cs);
	else if (ft_strncmp(cs[0], "export", 7) == 0)
		run_export(sh, cs);
	else if (ft_strncmp(cs[0], "unset", 6) == 0)
		run_unset(sh, cs);
	else if (ft_strncmp(cs[0], "env", 4) == 0)
		run_env(sh, cs);
	else if (ft_strncmp(cs[0], "exit", 5) == 0)
		run_exit(sh, cs);
	else
	{
		if (sh->child)
			run_one(sh, cs);
		else
			run_exe(sh, cs);
	}
	if (sh->child)
		exit(0);
}

int	have_pip(char **cs)
{
	int	i;

	i = 0;
	while (cs[i])
	{
		if (pip_redir(cs[i]))
			return (1);
		i++;
	}
	return (0);
}

void	exe_all(t_sh *sh, char **cs)
{
	if (have_pip(cs))
		run_row(sh, cs);
	else
	{
		sh->child = 0;
		exe_cmd(sh, cs);
	}
	free_all(cs);
}
