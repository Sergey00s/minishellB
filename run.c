/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:22:58 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/28 04:27:51 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

static void	run3_if(t_parsed *temp, t_list *parsed)
{
	if (temp->dlm)
		delim(temp, NULL, NULL);
	if (temp->input)
		dup2(temp->fd[0], 0);
	if (parsed->next || temp->output)
		dup2(temp->fd[1], 1);
	if (parsed->prev && !temp->input)
		dup2(((t_parsed *)(parsed->prev->content))->fd[0], 0);
	close(temp->pip[0]);
}

void	run3(t_list *parsed)
{
	int			id;
	t_parsed	*temp;

	temp = (t_parsed *)parsed->content;
	pipe(temp->pip);
	if (!temp->input)
		temp->fd[0] = temp->pip[0];
	if (!temp->output)
		temp->fd[1] = temp->pip[1];
	id = fork();
	if (id == 0)
	{
		if (temp->input == -2)
			error_exit(1, " ", "No such a file or directory!");
		run3_if(temp, parsed);
		if (temp->args && temp->args->lst && temp->args->lst[0])
			do_next(parsed, temp);
		exit(0);
	}
	close(temp->pip[1]);
	close(temp->fd[1]);
}
