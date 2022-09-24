/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fit_operations2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:40:12 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 17:29:43 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	*ft_putit(const char *s1, char c)
{
	char	*s2;
	int		i;
	int		j;

	s2 = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (s2 == 0)
		return (0);
	i = 0;
	j = 0;
	while (s1[j])
	{
		if (s1[j] != c)
		{
			s2[i] = s1[j];
			i++;
		}
		j++;
	}
	s2[i] = '\0';
	return (s2);
}

static void	fit_new_if(t_char2d *temp, int i)
{	
	char	*old;

	temp->type = 2;
	old = temp->lst[i];
	temp->lst[i] = ft_substr(old, 1, ft_strlen(old) - 2);
	free(old);
	old = temp->lst[i];
	temp->lst[i] = ft_putit(temp->lst[i], '\'');
	free(old);
}

static void	fit_new_else_if(t_char2d *temp, int i)
{
	char	*old;

	temp->type = 1;
	old = temp->lst[i];
	temp->lst[i] = ft_substr(old, 1, ft_strlen(old) - 2);
	free(old);
	old = temp->lst[i];
	temp->lst[i] = ft_putit(temp->lst[i], '"');
	free(old);
}

void	fit_redir(t_redir *redir)
{
	int	i;

	i = 0;
	while (redir)
	{
		ft_fixit(redir);
		redir = redir->next;
	}
}

void	fit_new(t_parsed *new)
{
	int			i;
	t_char2d	*temp;

	i = 0;
	temp = new->args;
	while (temp && temp->lst[i])
	{
		if (temp->lst[i][0] != '\'')
		{
			find_dollar_put(&temp->lst[i]);
			temp->type = 2;
		}
		if (temp->lst[i][0] == '\'')
			fit_new_if(temp, i);
		else if (temp->lst[i][0] == '"')
			fit_new_else_if(temp, i);
		else
		{
			if (!checkit(temp->lst[i]))
				temp->type = -1;
		}
		i++;
	}
	fit_redir(new->redirs);
}
