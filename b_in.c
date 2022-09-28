/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_in.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 06:09:20 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/28 05:42:32 by ialgac           ###   ########.fr       */
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

	home = NULL;
	if (!path || (path && *path == 0) || !ft_strncmp(path, "~", 1))
	{
		home = ft_findhome ();
		if (access(home, F_OK) != -1)
			chdir(home);
		else
		{
			print_error("minishell", home, "No such a file or directory");
			ft_myexport(ft_itoa(1));
			return 0;
		}
	}
	else
	{
		if (access(path, F_OK) != -1)
			chdir(path);
		else
		{
			print_error("minishell", home, "No such a file or directory");
			ft_myexport(ft_itoa(1));
			return 0;
		}
	}
	ft_myexport(ft_itoa(0));
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
