/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:22:42 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 17:22:43 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	move_to_right(char **arg, int i, int code)
{
	int		len;
	char	*new;

	len = ft_strlen(*arg);
	new = ft_calloc(len + 2, sizeof(len));
	ft_memmove(new, *arg, i);
	new[i] = ' ';
	ft_memmove(new + i + 1, *arg + i, len - i);
	i += 2;
	while (new[i])
	{
		if (new[i] == code)
		{
			if (new[i + 1] != ' ' && new[i + 1])
			{
				ft_memmove(new + i + 1, new + i, len - i + 1);
				new[i + 1] = ' ';
				break ;
			}
		}
		i++;
	}
	free(*arg);
	*arg = new;
}

void	movethem(char **arg, int i, int code)
{
	if (i > 0)
	{
		if (arg[0][i - 1] != ' ' && arg[0][i - 1] != '=')
		{
			move_to_right(arg, i, code);
		}
	}	
}

char	*removespace(char *arg, int i, int x)
{
	while (arg[i])
	{
		fix_pre_parse(isspclpar(arg[i], arg[i + 1]), &arg, i + 1);
		fix_post_parse(isspclpar2(arg, i), &arg, i - 1);
		if (arg[i] == ' ')
			cut_spaces(&arg, i + 1);
		if (arg[i] == '"')
		{
			i++;
			while (arg[i] && arg[i] != '"')
				i++;
		}
		if (arg[i] == '\'')
		{
			i++;
			while (arg[i] && arg[i] != '\'')
				i++;
		}
		i += (arg[i] != 0);
	}
	if (!pre_control(arg, ft_strlen(arg)))
		error_exit(-1);
	fit_quto(&arg, x);
	fit_env_var(&arg);
	return (arg);
}
