/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:40:27 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 16:48:47 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	*makeit(char *var, char *value)
{
	char	*rtn;
	char	*temp;

	if (value[0] == '"')
		value++;
	if (value[ft_strlen(value) - 1] == '"')
		value[ft_strlen(value) - 1] = 0;
	if (value[0] == 39)
		value++;
	if (value[ft_strlen(value) - 1] == 39)
		value[ft_strlen(value) - 1] = 0;
	temp = ft_strjoin(var, "=");
	rtn = ft_strjoin(temp, value);
	free(temp);
	return (rtn);
}

void	ft_expand(char *str)
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

int	ft_varcheck(char *var)
{
	int	i;

	if (!var)
	{
		return (0);
	}
	i = 1;
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	while (var[i])
	{
		if (!ft_isalpha(var[i]) && !ft_isdigit(var[i]) && var[0] != '_')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_toenv(char *var, char *value)
{
	int		i;
	char	*str;

	if (!ft_varcheck(var))
	{
		printf("%s Not valid arg\n", var);
		return ;
	}
	str = makeit(var, value);
	i = 0;
	while (g_stuff->env[i])
	{
		if (!ft_strncmp(g_stuff->env[i], var, ft_strlen(var)))
		{
			free(g_stuff->env[i]);
			g_stuff->env[i] = str;
			return ;
		}
		i++;
	}
	ft_expand(str);
}

void	ft_toenv2(char *str)
{
	int	i;

	if (!ft_varcheck(str))
	{
		printf("%s Not valid arg\n", str);
		return ;
	}
	str = ft_strdup(str);
	i = 0;
	while (g_stuff->env[i])
	{
		if (!ft_strncmp(g_stuff->env[i], str, ft_strlen(str)))
			return ;
		i++;
	}
	ft_expand(str);
}
