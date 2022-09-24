/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:40:51 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 17:18:31 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	*path_finder(char *s)
{
	char	*si;

	si = calloc (sizeof(char), strlen(s));
	getcwd(si, strlen(s));
	printf("%s\n", si);
	return (si);
}

static int	get_path_if_else(char *path, char **theway)
{
	int	acc;

	acc = checkacces(path);
	if (acc)
	{
		*theway = path;
		return (1);
	}
	else
	{
		ft_putstr_fd("Path Error\n", 2);
		return (0);
	}
}

int	get_path(char *path, char **theway)
{
	int		i;
	char	**line;
	char	*old;
	char	*temp;
	char	*envpath;

	i = 0;
	envpath = find_envpath(g_stuff->env);
	line = ft_split(envpath, ':');
	free(envpath);
	while (line[i])
	{
		old = ft_strjoin(line[i], "/");
		temp = ft_strjoin(old, path);
		free(old);
		if (checkacces(temp))
		{
			*theway = temp;
			free(line);
			return (1);
		}
		i++;
	}
	free(line);
	return (get_path_if_else(path, theway));
}
