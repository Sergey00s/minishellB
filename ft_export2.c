/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:40:34 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/28 04:36:38 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	sort_print(char **env)
{
	int		i;
	int		j;
	char	*temp;
	int		len;

	i = 0;
	len = lenof(env);
	while (i < len)
	{
		j = 0;
		while (j + 1 < len)
		{
			if (ft_strncmp(env[j], env[j + 1], ft_strlen(env[j])) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	ex_print(void)
{
	int	i;

	i = -1;
	while (g_stuff->exports && *(g_stuff->exports + ++i))
		printf("declare -x %s\n", *(g_stuff->exports + i));
}

void	ft_export(char **args)
{
	int	i;
	int	j;

	i = 0;
	if (!args[1])
	{
		fit_ex();
		sort_print(g_stuff->exports);
		ex_print();
		return ;
	}
	while (args[++i])
	{	
		j = 0;
		while (args[i][j++])
			if (args[i][j] == '=')
				break ;
		if (args[i][j] == '=')
		{
			args[i][j] = 0;
			ft_toenv(args[i], &args[i][j + 1]);
		}
		else
			ft_toenv2(args[i]);
	}
	ft_myexport(ft_itoa(0));
}

void	ft_checklast(char **rtn, char *var, char *str)
{
	int	i;

	i = 0;
	while (rtn[i])
	{
		if (!ft_strncmp(rtn[i], var, ft_strlen(var)))
			return ;
		i++;
	}
	rtn[i] = str;
	rtn[i + 1] = 0;
}
