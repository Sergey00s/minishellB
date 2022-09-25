/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structutils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:41:51 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 17:39:33 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	ft_parse2_while(t_char2d *temp, int len, char **parsed)
{
	t_parsed	*new;
	int			i;

	i = 0;
	while (len > i)
	{
		temp = chararr();
		new = str_init(temp);
		while (len > i && !isspcl(parsed[i]))
		{
			if (isredir(parsed[i]))
			{
				ft_redir_addback(&new->redirs, \
				ft_create(ft_strdup(parsed[i + 1]), ft_strdup(parsed[i])));
				i = i + 2;
				continue ;
			}
			temp->append(temp, ft_strdup(parsed[i++]));
		}
		ft_lstadd_back(&g_stuff->parsed, ft_lstnew(new));
		i++;
	}
}

void	fit_in_q(void)
{
	t_parsed *temp;
	t_list		*parsed;

	parsed = g_stuff->parsed;

	while (parsed)
	{
		temp = (t_parsed *)(parsed->content);
		if (temp->args && temp->args->lst)
		{
			fix_quote(temp->args->lst);
		}
		parsed = parsed->next;
	}
}

int	ft_parse2(char **parsed)
{	
	t_char2d	*temp;
	int			len;
	int			i;

	len = 0;
	while (parsed[len])
	{
		len++;
	}
	ft_parse2_while(temp, len, parsed);
	fit_in_q();
	i = 0;
	while (parsed[i])
	{
		free(parsed[i]);
		i++;
	}
	free(parsed);
	return (1);
}

t_parsed	*str_init(t_char2d *args)
{
	t_parsed	*rtn;

	rtn = malloc(sizeof(t_parsed) * 1);
	rtn->args = args;
	rtn->redirs = NULL;
	rtn->order = 0;
	rtn->type = -1;
	rtn->fd[0] = -1;
	rtn->fd[1] = -1;
	rtn->pip[0] = 0;
	rtn->pip[1] = 1;
	rtn->input = 0;
	rtn->output = 0;
	rtn->dlm = 0;
	rtn->wr = 0;
	rtn->bin = 0;
	return (rtn);
}
