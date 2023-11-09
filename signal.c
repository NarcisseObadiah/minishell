/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:40:34 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/08 00:04:53 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ctrl_c(int sig)
{
	sig = 0;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_newline(int sig)
{
	sig = 0;
	rl_on_new_line();
	g_exit_code = 130;
}

void	set_signal_b(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	rm_signal();
	sa.sa_handler = ctrl_c;
	sb.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sb, NULL);
}

void	sig_quit(int sig)
{
	f_print(2, "Quit: %d\n", sig);
	g_exit_code = 131;
}

void	set_signal_a(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	sa.sa_handler = sig_newline;
	sb.sa_handler = sig_quit;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sb, NULL);
}
