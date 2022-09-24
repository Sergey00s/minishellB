/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:39:27 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 18:20:30 by iyarikan         ###   ########.fr       */
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
		if (parsed->fd[0] == -1 && !dlm)
			parsed->input = -2;
	}
}

int	gosingle(t_parsed *parsed)
{
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

void	doit2(char *a)
{
	int		count;
	t_list	*parsed;

	count = 0;
	g_stuff->parsed = NULL;
	if (!ft_parse2(ft_strdup(a), 0, 0) || !check_parse(g_stuff->parsed))
	{
		free_stuff();
		printf("Parse sError\n");
		ft_myexport(ft_itoa(258));
		return ;
	}
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
	wait_this(count);
	free_stuff();
}
