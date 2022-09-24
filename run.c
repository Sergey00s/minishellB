/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:22:58 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 17:23:00 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

static void	run3_if(t_parsed *temp, t_list *parsed)
{
	if (temp->dlm == 2)
		delim(temp, NULL, NULL);
	if (temp->input && temp->dlm != 2)
		dup2(temp->fd[0], 0);
	if (parsed->next || temp->output)
		dup2(temp->fd[1], 1);
	if (parsed->prev && !temp->input && !temp->dlm)
		dup2(((t_parsed *)(parsed->prev->content))->fd[0], 0);
}

void	run3(t_list *parsed)
{
	int			id;
	t_parsed	*temp;
	int			pipes[2];

	temp = (t_parsed *)parsed->content;
	pipe(pipes);
	if (!temp->input && temp->dlm != 2)
		temp->fd[0] = pipes[0];
	if (!temp->output)
		temp->fd[1] = pipes[1];
	checkacces(temp->args->lst[0]);
	id = fork();
	if (id == 0)
	{
		if (temp->input == -2)
		{
			ft_putendl_fd("No such file or dir!", 2);
			exit(127);
		}
		run3_if(temp, parsed);
		do_next(parsed, temp);
	}
	close(temp->fd[1]);
	close(pipes[1]);
}
