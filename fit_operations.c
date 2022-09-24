/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fit_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:40:06 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 10:37:21 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	ft_isnot(char c)
{
	if (ft_isdigit(c) || ft_isalpha(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

char	*ft_getenvparam(char *var)
{
	int		i;
	char	*ret;

	i = 0;
	while (g_stuff->env[i])
	{
		if (!ft_strncmp(var, g_stuff->env[i], ft_strlen(var)))
		{
			ret = ft_strdup(g_stuff->env[i] + ft_strlen(var) + 1);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

void	putvar(char **str, char *var, int start, int end)
{
	char	*temp;
	char	*temp2;
	char	*envar;
	char	*temp3;
	char	*old;

	envar = ft_getenvparam(var + 1);
	if (!envar)
	{
		if (var && var[0] && var[1] == '?')
			envar = ft_itoa(g_stuff->code);
	}
	old = *str;
	temp = ft_substr(*str, 0, start);
	temp2 = ft_strjoin(temp, envar);
	temp3 = ft_substr(*str, end, ft_strlen(*str));
	*str = ft_strjoin(temp2, temp3);
	free(old);
	free(temp);
	free(temp2);
	free(temp3);
	free(envar);
}

void	find_dollar_put(char **str)
{
	int		i;
	int		j;
	char	*var;

	var = 0;
	i = 0;
	while ((*str)[i] != '$' && (*str)[i])
		i++;
	if ((*str)[i] == '$' && \
	(ft_isalpha(str[0][i + 1]) || str[0][i + 1] == '_' || str[0][i + 1] == '?'))
	{
		j = i + 1;
		while (ft_isnot((*str)[j]) == 1)
			j++;
		var = ft_substr(*str, i, j - i);
		if (var)
		{
			putvar(str, var, i, j);
		}
	}
}

int	checkit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (0);
		if (str[i] == '>')
			return (0);
		if (str[i] == '<')
			return (0);
		i++;
	}
	return (1);
}
