/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:39:27 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/26 20:13:57 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	init_fd(t_parsed *parsed)
{
	char	*wr;
	char	*rd;
	char	*owr;
	char	*dlm;

	wr = check_write(parsed);
	rd = check_read(parsed);
	owr = check_owr(parsed);
	dlm = check_dlm(parsed);
	if (wr || owr)
	{
		parsed->output = 1;
		if (parsed->wr == 2)
			parsed->fd[1] = open(wr, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			parsed->fd[1] = open(wr, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	if (rd || dlm)
	{
		parsed->input = 1;
		parsed->fd[0] = open(rd, O_RDONLY, 0644);
	}
	
}

int	gosingle(t_parsed *parsed)
{
	if (!parsed->args || !parsed->args->lst)
	{
		return (0);
	}
	
	if (check_build(parsed->args->lst, parsed))
		return (1);
	return (0);
}

void	wait_this(int count)
{
	int	i;

	i = 0;
	while (count--)
	{
		waitpid(-1, &i, 0);
		if (i >= 256)
		{
			i = i / 256;
		}
		ft_myexport(ft_itoa(i));
	}
}

void	doit2(char **a)
{
	int		count;
	t_list	*parsed;
	t_parsed *temp;

	count = 0;
	g_stuff->parsed = NULL;
	ft_parse2(a);
	parsed = g_stuff->parsed;
	if (parsed && !parsed->next && !parsed->prev)
		if (gosingle((t_parsed *)parsed->content))
			return ;
	while (parsed)
	{
		init_fd((t_parsed *)parsed->content);
		run3(parsed);
		parsed = parsed->next;
		count++;
	}
	parsed = g_stuff->parsed;
	while (parsed)
	{
		temp = (t_parsed *)parsed->content;
		close(temp->pip[0]);
		close(temp->pip[1]);
		parsed = parsed->next;
	}
	wait_this(count);
	free_stuff();
}
