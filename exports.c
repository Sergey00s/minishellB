/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exports.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:39:55 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 17:28:22 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	lenof(char **l)
{
	int	i;

	i = 0;
	while (l[i])
		i++;
	return (i);
}

void	fit_ex(void)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (g_stuff->exports && g_stuff->exports[i])
	{
		free(g_stuff->exports[i]);
		i++;
	}
	free(g_stuff->exports);
	i = 0;
	while (g_stuff->env[i])
		i++;
	g_stuff->exports = malloc((1 + i) * sizeof(char *));
	while (k < i)
	{
		g_stuff->exports[k] = ft_strdup(g_stuff->env[k]);
		k++;
	}
	g_stuff->exports[k] = NULL;
}

void	ft_fixit(t_redir *redir)
{
	int		i;
	int		k;
	char	*a;

	i = 0;
	k = 0;
	if (redir->file[0] == '"' || redir->file[0] == '\'')
	{
		a = ft_substr(redir->file, 1, ft_strlen(redir->file) - 2);
		free(redir->file);
		redir->file = a;
	}
}
