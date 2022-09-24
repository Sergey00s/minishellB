/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specialsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 21:35:39 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 10:27:29 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

static char	*ft_mystrchr(const char *s, int c)
{
	int				i;
	unsigned char	cchar;

	cchar = (unsigned char)c;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
		}
		if (s[i] == cchar)
			return ((char *)&s[i]);
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (0);
}

static int	cwords(const char *s, char c)
{
	int	rtn;

	rtn = 0;
	while (s && *s)
	{
		while (*s == c)
			s++;
		rtn += *s != 0;
		s = ft_mystrchr(s, c);
	}
	return (rtn);
}

char	**specialsplit(char const *s, char c)
{
	int		words;
	char	**rtn;
	int		i;
	size_t	len;

	words = cwords(s, c);
	rtn = malloc((words + 3) * sizeof(char *));
	if (!rtn)
		return (0);
	i = 0;
	while (i < words)
	{
		while (s && *s == c)
			s++;
		len = ft_mystrchr(s, c) - s;
		rtn[i] = ft_substr(s, 0, len);
		s += len;
		if (!rtn[i++])
			return (0);
	}
	rtn[i] = 0;
	return (rtn);
}
