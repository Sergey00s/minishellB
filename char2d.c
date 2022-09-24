/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:38:40 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/22 19:38:41 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	append(t_char2d *self, char *value)
{
	int		i;
	char	**temp;

	temp = self->lst;
	i = 0;
	self->lst = ft_calloc(sizeof(char *), (self->len + 3));
	self->len++;
	while (temp && temp[i])
	{
		self->lst[i] = temp[i];
		i++;
	}
	self->lst[i] = ft_strdup(value);
	self->lst[i + 1] = NULL;
	free(temp);
	free(value);
}

void	del(t_char2d *self)
{
	int	i;

	i = 0;
	while (self->lst && self->lst[i])
	{
		free(self->lst[i]);
		i++;
	}
	free(self->lst);
	free(self);
}

t_char2d	*chararr(void)
{
	t_char2d	*self;

	self = malloc(sizeof(t_char2d) * 1);
	self->append = append;
	self->del = del;
	self->lst = NULL;
	self->len = 0;
	self->type = 0;
	return (self);
}
