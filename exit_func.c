/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:21:52 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/28 04:27:04 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void print_error(char *shell, char *cmd, char*str)
{
	ft_putstr_fd(shell, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}



void	free_ex_env(void)
{
	int	i;

	i = 0;
	while (g_stuff->env && g_stuff->env[i])
	{
		free(g_stuff->env[i]);
		i++;
	}
	free(g_stuff->env);
	i = 0;
	while (g_stuff->exports && g_stuff->exports[i])
	{
		free(g_stuff->exports[i]);
		i++;
	}
	free(g_stuff->exports);
}

void	error_exit(int code, char *cmd, char *msg)
{
	print_error("minishell", cmd, msg);
	ft_myexport(ft_itoa(code));
	exit(code);
}
