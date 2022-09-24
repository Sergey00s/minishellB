/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsofutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:42:57 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/22 19:42:59 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	mystrcmp(const char *s1, const char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s1)));
}

int	typeof2(char *str, int start, int end)
{
	if (str[start - 1] == '|')
	{
		if (str[end] == '|')
			return (2);
		if (str[end] == '\0')
			return (3);
		return (2);
	}
	else if (str[start - 1] == '>')
	{
		if (str[start] == '>')
			return (10);
		else
			return (9);
	}
	else if (str[start - 1] == '<')
		return (11 + (str[start] == '<'));
	else
	{
		if (str[end] == '\0')
			return (1);
		return (2);
	}
	return (-1);
}

int	inquote(char *arg, int i)
{
	int	k;
	int	ret;
	int	ret2;
	int	j;

	j = i;
	k = j;
	while (arg[j++] != '"' && arg[j])
		ret = 1;
	while (arg[k--] != '"' && arg[k])
		ret2 = 1;
	if (ret == 1 && ret2 == 1)
		return (1);
	j = i;
	k = j;
	while (arg[j++] != '\'' && arg[j])
		ret = 1;
	while (arg[k--] != '\'' && arg[k])
		ret2 = 1;
	if (ret == 1 && ret2 == 1)
		return (1);
	return (0);
}
