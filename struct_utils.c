/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:23:35 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 17:23:37 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	isspclpar(char a, char b)
{
	if (a == '>' && b == '>')
	{
		return (1);
	}
	if (a == '<' && b == '<')
	{
		return (2);
	}
	if (a == '>')
	{
		return (3);
	}
	if (a == '<')
	{
		return (4);
	}
	if (a == '|')
	{
		return (5);
	}
	if (b == 0)
	{
		return (-1);
	}
	return (0);
}

int	isspclpar2(char *arg, int i)
{
	char	a;

	if (i < 1)
		return (0);
	a = arg[i];
	if (a == '>')
		return (1);
	if (a == '<')
		return (2);
	if (a == '|')
		return (5);
	if (a == 0)
		return (-1);
	return (0);
}

int	isspcl2(char *str)
{
	if (str && !ft_strncmp(str, "|", 1))
		return (PP);
	if (str && !ft_strncmp(str, ">>", ft_strlen(str)))
		return (PP);
	if (str && !ft_strncmp(str, ">", ft_strlen(str)))
		return (PP);
	if (str && !ft_strncmp(str, "<", ft_strlen(str)))
		return (PP);
	if (str && !ft_strncmp(str, "<<", ft_strlen(str)))
		return (PP);
	return (0);
}

int	isspcl(char *str)
{
	if (str && !ft_strncmp(str, "|", 1))
		return (PP);
	return (0);
}

int	isredir(char *str)
{
	if (!ft_strncmp(str, ">>", ft_strlen(str)))
		return (1);
	if (*str && !ft_strncmp(str, ">", ft_strlen(str)))
		return (1);
	if (*str && !ft_strncmp(str, "<", ft_strlen(str)))
		return (1);
	if (*str && !ft_strncmp(str, "<<", ft_strlen(str)))
		return (1);
	return (0);
}
