/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokencheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:42:02 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/22 19:42:03 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	check2(char **parsed, int i)
{
	if (i <= 0)
		return (0);
	if (!parsed[i + 1])
		return (0);
	if (!ft_strncmp(parsed[i + 1], "<<", 2))
		return (0);
	if (i <= 0)
		return (0);
	if (!ft_strncmp(parsed[i + 1], ">>", 2))
		return (0);
	if (i <= 0)
		return (0);
	if (!ft_strncmp(parsed[i + 1], "<", 1))
		return (0);
	if (i <= 0)
		return (0);
	if (!ft_strncmp(parsed[i + 1], ">", 2))
		return (0);
	if (i <= 0)
		return (0);
	if (!ft_strncmp(parsed[i + 1], "|", 1))
		return (0);
	return (1);
}

int	checkorderof(char **parsed)
{
	int	i;

	i = 0;
	while (parsed[i])
	{
		if (!ft_strncmp(parsed[i], ">>", 2))
			if (!check2(parsed, i))
				return (0);
		if (!ft_strncmp(parsed[i], ">>", 2))
			if (!check2(parsed, i))
				return (0);
		if (!ft_strncmp(parsed[i], ">", 1))
			if (!check2(parsed, i))
				return (0);
		if (!ft_strncmp(parsed[i], "<", 1))
			if (!check2(parsed, i))
				return (0);
		if (!ft_strncmp(parsed[i], "|", 1))
			if (!check2(parsed, i))
				return (0);
		i++;
	}
	return (1);
}
