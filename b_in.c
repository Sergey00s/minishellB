/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_in.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 06:09:20 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 10:23:09 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	*ft_findhome(void)
{
	int		i;

	i = 0;
	while (g_stuff->env[i] && ft_strncmp("HOME=", g_stuff->env[i], 5))
		i++;
	if (g_stuff->env[i] && !ft_strncmp("HOME=", g_stuff->env[i], 5))
		return (g_stuff->env[i] + 5);
	return (NULL);
}

int	ft_change_dir(char *path)
{
	char	*home;

	if (!path || (path && *path == 0) || !ft_strncmp(path, "~", 1))
	{
		home = ft_findhome ();
		if (access(home, F_OK) != -1)
			chdir(home);
		else
			ft_putstr_fd("No such a file or dir\n", 2);
	}
	else
	{
		if (access(path, F_OK) != -1)
			chdir(path);
		else
			ft_putstr_fd("No such a file or dir\n", 2);
	}
	return (1);
}

void	ft_env(void)
{
	int	i;

	i = 0;
	while (g_stuff->env[i])
	{
		if (is_in(g_stuff->env[i], '='))
			printf("%s\n", g_stuff->env[i]);
		i++;
	}
}

int	ft_exit(char **arg)
{
	int	i;

	i = 0;
	if (arg && arg[0] && arg[1] && arg[2] != NULL)
	{
		ft_myexport(ft_itoa(1));
		return (0);
	}
	if (arg[1])
	{
		i = ft_atoi(arg[1]);
		exit(i);
	}
	ft_myexport(ft_itoa(0));
	exit(0);
}

int	check_build(char **args, t_parsed *parsed)
{
	if (!ft_strncmp(args[0], "cd", 2) || !ft_strncmp(args[0], "exit", 4) || \
	!ft_strncmp(args[0], "echo", 4) || !ft_strncmp(args[0], "env", 3) || \
	!ft_strncmp(args[0], "export", 6) || !ft_strncmp(args[0], "unset", 5))
	{
		parsed->bin = 1;
		init_fd(parsed);
		if (!ft_strncmp(args[0], "cd", 2))
			ft_change_dir(args[1]);
		else if (!ft_strncmp(args[0], "exit", 4))
			ft_exit(args);
		else if (!ft_strncmp(args[0], "echo", 4))
			ft_echo(args, parsed);
		else if (!ft_strncmp(args[0], "env", 3))
			ft_env2();
		else if (!ft_strncmp(args[0], "export", 6))
			ft_export(args);
		else if (!ft_strncmp(args[0], "unset", 5))
			ft_unset(args);
		return (1);
	}
	return (0);
}
