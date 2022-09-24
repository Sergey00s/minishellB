/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:41:43 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 12:23:50 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	fix_post_parse(int code, char **arg, int pos)
{
	if (code == 1 && arg[0][pos] != ' ' && arg[0][pos] != '>' )
	{
		put_new2(arg, pos);
	}
	else if (code == 2 && (*arg)[pos] != ' ' && arg[0][pos] != '<' )
	{
		put_new2(arg, pos);
	}
	else if (code >= 3 && (*arg)[pos] != ' ')
	{
		put_new2(arg, pos);
	}
	else if (code == 0)
	{
		return ;
	}
}

static void	ft_sec(char *arg, int *i)
{
	(*i)++;
	while (arg[*i] != 39)
			(*i)++;
	(*i)++;
}

static void	ft_sec2(char *arg, int *i, int *last)
{
	(*i)++;
	(*last) = *i;
	while (arg[*last] != '"')
		(*last)++;
}

static void	ft_sec3(char *arg, int *i)
{
	while (arg[*i] != '"')
		(*i)++;
	(*i)++;
}

void	fit_env_var(char **arg)
{
	int	i;
	int	last;

	i = 0;
	while (arg[0][i])
	{
		if (arg[0][i] == '"')
		{
			ft_sec2(*arg, &i, &last);
			put_them2(i, last + 1, arg, 0);
			ft_sec3(*arg, &i);
			continue ;
		}
		if (arg[0][i] == 39)
		{
			ft_sec(arg[0], &i);
			continue ;
		}
		last = i;
		while (arg[0][last] && arg[0][last] != 39 && arg[0][last] != '"')
			last++;
		put_them2(i, last + 1, arg, 0);
		while (arg[0][i] && arg[0][i] != 39 && arg[0][i] != '"')
			i++;
	}
}
