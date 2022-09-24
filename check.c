/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:38:53 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 16:27:47 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	checkacces(char *temp)
{
	if (access(temp, F_OK) != -1)
	{
		if (access(temp, X_OK) != -1)
		{
			ft_myexport(ft_itoa(0));
			return (1);
		}
		ft_putendl_fd("Not Executable!!", 2);
		ft_myexport(ft_itoa(126));
		return (0);
	}
	ft_myexport(ft_itoa(127));
	return (0);
}

int	checkorder(t_parsed *parsed)
{
	int	i;

	i = 0;
	if (!parsed->args->lst)
		return (0);
	return (1);
}

int	check_parse(t_list *lst)
{
	t_parsed	*parsed;
	int			i;

	i = 0;
	while (lst)
	{
		if (!lst->content)
			return (0);
		parsed = (t_parsed *)lst->content;
		if (!checkorder(parsed))
			return (0);
		if (!checkpipes(parsed))
			return (0);
		if (!checkredirs(parsed))
			return (0);
		if (parsed->args->type == -1)
			return (0);
		lst = lst->next;
	}
	return (1);
}
