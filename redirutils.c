/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:41:15 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/27 23:23:35 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	*check_write(t_parsed *parsed)
{
	char	*ret;
	t_redir	*redirs;

	ret = 0;
	redirs = parsed->redirs;
	while (redirs)
	{
		if (!ft_strncmp(redirs->type, ">", 1) \
		|| !ft_strncmp(redirs->type, ">>", 2))
		{
			ret = redirs->file;
			if (!ft_strncmp(redirs->type, ">>", 2))
				parsed->wr = 2;
			else
			{
				parsed->wr = 1;
			}
			close(open(ret, O_CREAT, 0644));
		}
		redirs = redirs->next;
	}	
	return (ret);
}

char	*check_owr(t_parsed *parsed)
{
	char	*ret;
	t_redir	*redirs;

	ret = 0;
	redirs = parsed->redirs;
	while (redirs)
	{
		if (!ft_strncmp(redirs->type, ">>", 2))
		{
			ret = redirs->file;
			close(open(ret, O_CREAT, 0644));
		}
		redirs = redirs->next;
	}
	return (ret);
}

char	*check_read(t_parsed *parsed)
{
	char	*ret;
	t_redir	*redirs;

	ret = 0;
	redirs = parsed->redirs;
	while (redirs)
	{
		if (!ft_strncmp(redirs->type, "<", 1))
		{
			ret = redirs->file;
			close(open(ret, O_RDONLY, 444));
		}
		redirs = redirs->next;
	}
	return (ret);
}

char	*check_dlm(t_parsed *parsed)
{
	char	*ret;
	t_redir	*redirs;

	ret = 0;
	redirs = parsed->redirs;
	parsed->dlm = 0;
	while (redirs)
	{
		if (!ft_strncmp(redirs->type, "<<", 2))
		{
			ret = redirs->file;
			parsed->dlm = 1;
		}
		redirs = redirs->next;
	}
	return (ret);
}

void	closepipes(t_list *parsed)
{
	t_parsed	*temp;

	while (parsed)
	{
		temp = (t_parsed *)parsed->content;
		close(temp->fd[0]);
		close(temp->fd[1]);
		parsed = parsed->next;
	}	
}
