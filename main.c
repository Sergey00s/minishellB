/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:40:43 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/28 06:00:10 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"
#include <readline/history.h>
#include <readline/readline.h>

t_stuff	*g_stuff;

void	delim_ch(char **buffer, char *key, t_redir *tmp, char *line)
{
	char	*tmpbuf;

	while (1)
	{
		while (line)
		{
			tmpbuf = *buffer;
			line = readline("> ");
			if (!strcmp_abs(line, key))
				break ;
			line = ft_strjoin(line, "\n");
			*buffer = ft_strjoin(*buffer, line);
			free(line);
			free(tmpbuf);
		}
		if (tmp)
			tmp = tmp->next;
		tmp_next(&tmp, &key);
		if (!tmp)
			break ;
		free(*buffer);
		*buffer = 0;
	}
}

void	delim(t_parsed *parsed, char *line, char *key)
{
	char	*buffer;
	t_redir	*tmp;
	int		ownpipe[2];
	
	buffer = 0;
	key = 0;
	tmp = parsed->redirs;
	tmp_next(&tmp, &key);
	line = readline("> ");
	if (!strcmp_abs(line, key))
	{
		free(line);
		delim_wr(ownpipe, "", parsed);
		return;
	}
	line = ft_strjoin(line, "\n");
	buffer = ft_strdup(line);
	free(line);
	line = "";
	delim_ch(&buffer, key, tmp, line);
	delim_wr(ownpipe, buffer, parsed);
}

void	do_next(t_list *parsed, t_parsed *temp)
{
	char	*way;
	int		path;

	if (check_build(((t_parsed *)parsed->content)->args->lst, temp))
		exit(0);
	path = get_path(temp->args->lst[0], &way);
	if (path != -1 && path != 0)
	{
		if (execve(way, temp->args->lst, g_stuff->env) == -1)
		{
			error_exit(127, temp->args->lst[0], "Command not found!");
		}
	}
	exit(0);
}

void iss_to_s(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			str[i] = ' ';
		i++;
	}
}

int	getin(int ac)
{
	char	*c;
	char	**preparsed;

	(void)ac;
	c = readline("MiniBeachShell $> ");
	if (c && *c)
	{
		iss_to_s(c);
		preparsed = pre_parse(c);
		if (!preparsed)
			return 1;
		doit2(preparsed);
		add_history(c);
	}
	if (!c)
		return (0);
	free(c);
	return (1);
}

int	main(int ac, char **av, char **menv)
{	
	g_stuff = malloc(sizeof(t_stuff));
	g_stuff->env = putmenv(menv);
	g_stuff->exports = NULL;
	g_stuff->checker = 0;
	g_stuff->code = 0;
	fit_ex();
	ft_myexport(ft_itoa(0));
	go(ac, av);
	return (0);
}
