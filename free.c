/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:40:17 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 18:03:39 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	free_parsed(t_parsed *parsed)
{
	int		i;
	t_redir	*old;

	i = 0;
	old = parsed->redirs;
	while (parsed->redirs)
	{
		old = parsed->redirs;
		free(parsed->redirs->file);
		free(parsed->redirs->type);
		parsed->redirs = parsed->redirs->next;
		free(old);
	}
	parsed->args->del(parsed->args);
	free(parsed);
}

void	free_stuff(void)
{
	t_list	*temp;

	while (g_stuff->parsed)
	{
		free_parsed((t_parsed *)g_stuff->parsed->content);
		temp = g_stuff->parsed->next;
		free(g_stuff->parsed);
		g_stuff->parsed = temp;
	}
	free(g_stuff->parsed);
}
