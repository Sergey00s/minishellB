/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:42:51 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/22 20:29:21 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	jump_till_not(char **str, char *set)
{
	while (str && *str && **str && !is_in(set, **str))
		(*str)++;
}

void	jump_till(char **str)
{
	if (str && *str && !ft_isalpha(**str) && **str != '_')
		return ;
	while (**str)
	{
		if (!ft_isalpha(**str) && !ft_isdigit(**str) && **str != '_')
		{
			return ;
		}
		(*str)++;
	}
}

char	*find_var_env(char **menv, char *var)
{
	int	i;

	i = 0;
	while (menv && menv[i])
	{
		if (!ft_strncmp(menv[i], var, \
		ft_strlen(var)) && menv[i][ft_strlen(var)] == '=')
		{
			return (ft_strdup(&(menv[i][ft_strlen(var) + 1])));
		}
		i++;
	}
	return (NULL);
}

int	checkifinq(char *str, int i)
{
	int	back;
	int	front;
	int	backq;
	int	frontq;

	back = 0;
	front = -1;
	backq = 0;
	frontq = 0;
	while (i + back >= 0 && str[back + i])
	{
		if (str[back + i] == '\'')
		{
			backq = 1;
			break ;
		}
		back--;
	}
	while (str[i + ++front])
	{
		if (str[back + i] == '\'')
			if (backq == 1)
				return (1);
	}
	return (backq == 1 && frontq == 1);
}
