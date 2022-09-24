/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:24:09 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 17:24:10 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	put_new(char **arg, int pos)
{
	int		i;
	char	*new;
	int		j;

	i = 0;
	new = malloc((ft_strlen(*arg) + 2) * sizeof(char));
	while (i <= pos)
	{
		new[i] = arg[0][i];
		i++;
	}
	j = i;
	new[i] = ' ';
	i++;
	while (arg[0][j])
	{
		new[i] = arg[0][j];
		i++;
		j++;
	}
	new[i] = 0;
	free(*arg);
	*arg = new;
}

void	put_new2(char **arg, int pos)
{
	int		i;
	char	*new;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(*arg);
	new = malloc((ft_strlen(*arg) + 2) * sizeof(char));
	while (i <= pos)
	{
		new[i] = arg[0][i];
		i++;
	}
	new[i] = ' ';
	j = i;
	i++;
	while (arg[0][j])
		new[i++] = arg[0][j++];
	new[i] = 0;
	free(*arg);
	*arg = new;
}

void	put_them2(int start, int end, char **arg, int i)
{
	t_vars	vars;
	char	*var;
	char	*value;
	char	*temp;

	i = -1;
	while (g_stuff->env[++i])
	{
		temp = get_till(g_stuff->env[i], '=');
		var = ft_strjoin("$", temp);
		free(temp);
		value = get_after(g_stuff->env[i], '=');
		vars.start = start;
		vars.last = end;
		temp = format(*arg, var, value, vars);
		free(value);
		free(var);
		if (temp != NULL)
		{
			free(*arg);
			*arg = temp;
			break ;
		}
		free(temp);
	}
}

void	fit_quto(char **arg, int x)
{
	int	i;

	x = 0;
	i = -1;
	while (arg[0][++i])
	{
		if (arg[0][i] == '"')
		{
			movethem(arg, i, '"');
			i = i + 2;
			while (arg[0][i] && arg[0][i] != '"')
				i++;
			if (!arg[0][i])
				return ;
		}
		else if (arg[0][i] == 39)
		{
			movethem(arg, i, 39);
			i = i + 2;
			while (arg[0][i] && arg[0][i] != 39)
				i++;
			if (!arg[0][i])
				return ;
		}
	}
}

void	fix_pre_parse(int code, char **arg, int pos)
{
	if (code == 1 && (*arg)[pos + 2] != ' ')
	{
		put_new(arg, pos);
	}
	else if (code == 2 && (*arg)[pos + 2] != ' ')
	{
		put_new(arg, pos);
	}
	else if (code >= 3 && (*arg)[pos + 1] != ' ')
	{
		put_new(arg, pos - 1);
	}
	else if (code == 0)
	{
		return ;
	}
}
