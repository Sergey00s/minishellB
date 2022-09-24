/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirfunc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:41:07 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/22 19:41:09 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

t_redir	*ft_create(char *file, char *type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	new->file = file;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_redir	*ft_redirlast(t_redir *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_redir_addback(t_redir **lst, t_redir *new)
{
	t_redir	*temp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_redirlast(*lst);
	temp->next = new;
	new->prev = temp;
}
