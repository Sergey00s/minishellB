/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:39:11 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 18:22:47 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	delim_wr(int *pipes, char *buffer, t_parsed *parsed)
{
	if (parsed->dlm == 2)
	{
		pipe(pipes);
		write(pipes[1], buffer, ft_strlen(buffer));
		if (parsed->bin != 1)
			dup2(pipes[0], 0);
		close(pipes[1]);
	}
}

void	tmp_next(t_redir **tmp, char **key)
{
	while (*tmp)
	{
		if (!ft_strncmp((*tmp)->type, "<<", 2))
		{
			*key = (*tmp)->file;
			break ;
		}
		(*tmp) = (*tmp)->next;
	}
}
