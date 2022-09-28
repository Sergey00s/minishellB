/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:42:22 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/28 06:06:42 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	put_in(char **rtn, char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (g_stuff->env[i] && arg)
	{
		if (!ft_strncmp(g_stuff->env[i], arg, ft_strlen(arg)))
		{
			free(g_stuff->env[i]);
			i++;
			continue ;
		}
		rtn[j] = g_stuff->env[i];
		i++;
		j++;
	}
	rtn[j] = 0;
	free(g_stuff->env);
	g_stuff->env = rtn;
}

void	unset_this(char *arg)
{
	int		i;
	int		len;
	char	**rtn;

	len = 0;
	while (g_stuff->env[len])
		len++;
	i = 0;
	while (g_stuff->env[i] && arg)
	{
		if (!ft_strncmp(g_stuff->env[i], arg, ft_strlen(arg)))
		{
			rtn = ft_calloc(sizeof(char *), len + 2);
			put_in(rtn, arg);
			fit_ex();
			break ;
		}
		i++;
	}
}

void	ft_unset(char **args)
{
	int	i;
	char *a;

	i = 1;
	while (args[i])
		i++;
	i = 1;
	while (args && args[i])
	{
		if (args[i])
		{
			a = ft_strdup(args[i]);
			unset_this(a);
			free(a);
		}
		i++;
	}
	ft_myexport(ft_itoa(0));
}
