/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringformat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:23:15 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 17:23:18 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	is_ok(char c)
{
	if (ft_isalpha(c))
		return (0);
	if (ft_isdigit(c))
		return (0);
	if (c == '_')
		return (0);
	return (1);
}

char	*format(char *str, char *var, char *value, t_vars vars)
{
	vars.len = ft_strlen(var);
	vars.i = vars.start;
	vars.rtn = 0;
	while (vars.i < vars.last)
	{
		if (!ft_strncmp(&str[vars.i], var, vars.len) && \
		is_ok(str[vars.i + vars.len]))
		{
			vars.front = ft_substr(str, 0, vars.i);
			vars.end = ft_substr(str, vars.i + vars.len, ft_strlen(str));
			vars.temp = ft_strjoin(vars.front, value);
			free(vars.front);
			vars.front = ft_strjoin(vars.temp, vars.end);
			free(vars.end);
			free(vars.temp);
			free(vars.rtn);
			vars.rtn = vars.front;
			str = vars.rtn;
			vars.i = vars.i + vars.len;
			vars.last += ft_strlen(value) - vars.len;
		}
		vars.i++;
	}
	return (vars.rtn);
}
