/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:22:24 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 17:22:27 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	*get_after(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			return (ft_substr(str, i + 1, ft_strlen(str)));
		}	
		i++;
	}
	return (NULL);
}

char	*get_till(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			return (ft_substr(str, 0, i));
		}	
		i++;
	}
	return (NULL);
}

void	cut_spaces(char **arg, int i)
{
	int	j;

	j = i;
	while ((*arg)[j] && ft_isspace((*arg)[j]))
		j++;
	while ((*arg)[j])
	{
		(*arg)[i] = (*arg)[j];
		i++;
		j++;
	}
	(*arg)[i] = 0;
}

void	go_for2(char *arg, int *i, int *q, int c)
{
	if (arg && arg[*i] == c)
	{
		(*q)++;
		(*i)++;
		while (arg[*i] && arg[*i] != c)
			(*i)++;
		if (arg[*i] == c)
			(*q)++;
	}
}

int	pre_control(char *arg, int len)
{
	int	i;
	int	dq;
	int	q;

	i = 0;
	dq = 0;
	q = 0;
	while (i < len)
	{
		go_for2(arg, &i, &dq, '"');
		go_for2(arg, &i, &q, 39);
		i++;
	}
	if (dq % 2 != 0 || q % 2 != 0)
		return (0);
	return (1);
}
