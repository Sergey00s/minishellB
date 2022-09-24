/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myexport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:21:37 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 17:21:39 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	ft_myexpand(char *str)
{
	int		len;
	char	**rtn;
	int		i;

	len = 0;
	while (g_stuff->env[len])
		len++;
	rtn = malloc(sizeof(char *) * (len + 3));
	i = 0;
	while (g_stuff->env[i])
	{
		rtn[i] = g_stuff->env[i];
		i++;
	}
	rtn[i] = str;
	rtn[i + 1] = NULL;
	free(g_stuff->env);
	g_stuff->env = rtn;
}

void	ft_tomyenv(char *str)
{
	int		i;

	i = 0;
	while (g_stuff->env[i])
	{
		if (!ft_strncmp(g_stuff->env[i], "?", 1))
		{
			free(g_stuff->env[i]);
			g_stuff->env[i] = str;
			return ;
		}
		i++;
	}
	ft_myexpand(str);
}

int	ft_myexport(char *value)
{
	char	*temp;

	temp = ft_strjoin("?=", value);
	free(value);
	ft_tomyenv(temp);
	return (1);
}
