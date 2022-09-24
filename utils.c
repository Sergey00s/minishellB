/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:42:45 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/22 19:42:46 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	find_space_count(char *arg, int j)
{
	while (arg[j] != ' ')
	{
		j++;
	}
	return (j);
}

char	*find_envpath(char **env)
{
	char	*env_path;
	int		i;

	env_path = NULL;
	i = 0;
	while (env[i])
	{
		if (!strncmp(env[i], "PATH=", 5))
			env_path = ft_substr(env[i], 5, ft_strlen(env[i]));
		i++;
	}
	return (env_path);
}

int	is_in(char *set, int c)
{
	int	i;

	i = 0;
	while (set && set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	jump_to_char(char **str, char c)
{
	while (str && *str && **str && **str != c)
		(*str) = (*str) + 1;
}

void	jump_spaces(char **str)
{
	while (str && *str && **str == ' ')
		(*str)++;
}
