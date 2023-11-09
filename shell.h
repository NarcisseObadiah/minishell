/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 03:31:59 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/09 17:33:13 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>

long long	g_exit_code;

typedef struct s_sh
{
	int		runing;
	char	*pwd;
	char	*odpwd;
	char	**env;
	char	*home;
	char	*user;
	char	**evpth;
	int		exit_code;
	int		child;
	int		fout;
	int		fin;
	int		sout;
	int		sin;
	int		pin;
	int		pout;
	int		pid;
}	t_sh;

int			f_print(int fd, const char *s, ...);

char		*sjoin(char const *s1, char const *s2);
char		*sjoin_f1(char const *s1, char const *s2);
char		*sjoin_f2(char const *s1, char const *s2);
size_t		ft_strlen(const char *str);
char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *src);
char		*ft_sdupf(const char *src);
int			ft_strncmp(const char *s1, const char *s2, int n);
long long	ft_atoi(const char *str);

void		set_env(t_sh *shell);
void		set_env_r(t_sh *shell);
void		set_envpth(t_sh *sh);
void		set_signal_b(void);
void		set_signal_a(void);
void		rm_signal(void);
int			find(char **str, char *s);

char		**prase(t_sh *sh, char **cs);
void		write_quo(char c, char *re, int *j, int in_quo);
int			write_dolor(char *c, t_sh *sh, char *re, int *j);

void		exe_cmd(t_sh *sh, char **cs);
void		exe_all(t_sh *sh, char **cs);
char		*get_pth(char **evpth, char *cs);

char		pip_redir(char *s);
int			*split_pos(char **cs);
char		**get_cmd(char **cs, int *inx, int i);
char		***split_cmd(char **cs);
void		each_cmd(char ***css, char **cs, int *inx, int *i);
void		vaild(char **cs);
char		***reload(char ***css);
// void	get_cmd(char **cs, int *inx, int i, char ***csi);

void		run_echo(t_sh *sh, char **cs);
void		run_pwd(t_sh *sh, char **cs);
void		run_cd(t_sh *sh, char **cs);
void		run_env(t_sh *sh, char **cs);
void		env_append(t_sh *sh, char *cs);
void		env_delete(t_sh *sh, int i);
void		run_export(t_sh *sh, char **cs);
int			is_aphnum(char c);
char		*prase_exp(char *cs);
int			valid_exp(char *s);
void		run_unset(t_sh *sh, char **cs);
void		run_exit(t_sh *sh, char **cs);

void		run_pip(t_sh *sh, char **cs);
void		run_row(t_sh *sh, char **cs);
void		run_one(t_sh *sh, char **cs);
void		redir(t_sh *sh, char ***css, int *i);

void		free_all(char **cs);
void		free_sh(t_sh *sh);

#endif