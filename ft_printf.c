/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiqin <tiqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 05:21:57 by tiqin             #+#    #+#             */
/*   Updated: 2023/11/07 23:48:26 by tiqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

void	print_c(int fd, int c, int *count)
{
	write(fd, &c, 1);
	(*count)++;
}

void	print_s(int fd, char *s, int *count)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
	else
	{
		write(fd, "(null)", 6);
		i = 6;
	}
	(*count) += i;
}

void	print_i(int fd, int nb, int *count)
{
	char	c;

	c = 0;
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		*count += 11;
	}
	else if (nb < 0)
	{
		write(fd, &"-", 1);
		(*count)++;
		print_i(fd, -nb, count);
	}
	else if (nb <= 9)
	{
		c = nb + 48;
		write(fd, &c, 1);
		(*count)++;
	}
	else
	{
		print_i(fd, nb / 10, count);
		print_i(fd, nb % 10, count);
	}
}

void	print_con(int fd, char t, va_list args, int *len)
{
	if (t == '%')
		print_c(fd, '%', len);
	else if (t == 'c')
		print_c(fd, va_arg(args, int), len);
	else if (t == 's')
		print_s(fd, va_arg(args, char *), len);
	else if (t == 'd' || t == 'i')
		print_i(fd, va_arg(args, int), len);
}

int	f_print(int fd, const char *s, ...)
{
	va_list	args;
	int		len;
	size_t	i;

	i = 0;
	len = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] != '%')
		{
			write(fd, &s[i++], 1);
			len++;
		}
		else
		{
			i++;
			print_con(fd, s[i], args, &len);
			i++;
		}
	}
	va_end(args);
	return (len);
}
