/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:21:52 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 17:21:53 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

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

void	error_exit(int code)
{
	if (code == -1)
	{
		ft_putstr_fd("Quote Error", 2);
		exit(0);
	}
}
