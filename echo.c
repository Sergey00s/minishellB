/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:39:44 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 10:24:58 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

static int	args_cnt(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

void	eccho(int fd, char **args)
{
	int		i;
	int		control;

	i = 1;
	control = 0;
	if (args_cnt(args) > 1)
	{
		while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
		{
			control = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], fd);
			if (args[i + 1] && args[i][0] != '\0')
				write(fd, " ", 1);
			i++;
		}
	}
	if (control == 0)
		write(fd, "\n", 1);
}

int	ft_echo(char **args, t_parsed *parsed)
{
	if (parsed->dlm)
		delim(parsed, NULL, NULL);
	if (parsed->output)
		eccho(parsed->fd[1], args);
	else
		eccho(1, args);
	return (0);
}

void	ft_env2(void)
{
	char	**env;
	int		i;
	int		j;

	i = 0;
	env = g_stuff->env;
	while (env[i])
	{
		j = 0;
		if (env[i][0] == '?')
		{
			i++;
			continue ;
		}
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				printf("%s\n", env[i]);
				break ;
			}
			j++;
		}
		i++;
	}
}
