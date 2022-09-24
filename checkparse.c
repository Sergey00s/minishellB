/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkparse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:39:03 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/22 19:39:04 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	checkpipes(t_parsed *parsed)
{
	char	**arg;
	int		i;

	arg = parsed->args->lst;
	i = 0;
	while (arg[i])
		i++;
	if (i > 0)
	{
		if (!ft_strncmp(arg[i - 1], "|", 1))
			return (0);
	}
	return (1);
}

int	checkredirstypes(char *type)
{
	if (!ft_strncmp(type, "<<", 2) && ft_strlen(type) == 2)
		return (1);
	if (!ft_strncmp(type, "<", 1) && ft_strlen(type) == 1)
		return (1);
	if (!ft_strncmp(type, ">>", 2) && ft_strlen(type) == 2)
		return (1);
	if (!ft_strncmp(type, ">", 1) && ft_strlen(type) == 1)
		return (1);
	return (0);
}

int	checkredirfiles(char *filename)
{
	if (filename && *filename != 0)
		return (1);
	return (0);
}

int	checkredirs(t_parsed *parsed)
{
	t_redir	*redir;

	redir = parsed->redirs;
	while (redir)
	{
		if (!checkredirstypes(redir->type))
			return (0);
		if (!checkredirfiles(redir->file))
			return (0);
		redir = redir->next;
	}
	return (1);
}
