/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:40:51 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/28 05:44:56 by ialgac           ###   ########.fr       */
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

// static int	get_path_if_else(char *path, char **theway)
// {
// 	int	acc;

// 	acc = checkacces(path);
// 	if (acc)
// 	{
// 		*theway = path;
// 		return (1);
// 	}
// 	else
// 	{
// 		error_exit(127, path, "none");
// 		return (0);
// 	}
// }

int	check_abs(char *path)
{
	return(checkacces(path));
}

int	get_path(char *path, char **theway)
{
	int		i;
	char	**line;
	char	*old;
	char	*temp;

	temp = find_envpath(g_stuff->env);
	line = ft_split(temp, ':');
	free(temp);
	if(is_in(path, '/') && check_abs(path))
	{
		*theway = path;
		free(line);
		return 1;
	}
	else if (is_in(path, '/'))
		error_exit(127, path, "No such a file or directory");
	
	i = 0;
	while (line[i])
	{
		old = ft_strjoin(line[i], "/");
	 	temp = ft_strjoin(old, path);
		free(old);
		if (checkacces(temp))
		{
			*theway = temp;
			//all fre line
			free(line);
			return 1;
		}
		i++;
	}
	error_exit(127, path, "command not found");
	return (0);
}
