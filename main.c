/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:40:43 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 18:25:50 by iyarikan         ###   ########.fr       */
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
			if (!ft_strncmp(line, key, ft_strlen(key)))
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
	int		pipes[2];
	t_redir	*tmp;

	buffer = 0;
	key = 0;
	tmp = parsed->redirs;
	tmp_next(&tmp, &key);
	line = readline("> ");
	line = ft_strjoin(line, "\n");
	buffer = ft_strdup(line);
	free(line);
	line = "";
	if (!ft_strncmp(buffer, key, ft_strlen(key)))
	{
		pipe(pipes);
		if (parsed->bin != 1)
			dup2(pipes[0], 0);
		close(pipes[1]);
		free(buffer);
		return ;
	}
	delim_ch(&buffer, key, tmp, line);
	delim_wr(pipes, buffer, parsed);
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
			ft_putnbr_fd(path, 2);
			ft_putstr_fd(" %d not x able\n", 2);
			ft_myexport(ft_itoa(127));
		}
	}
	ft_myexport(ft_itoa(127));
	exit(1);
}

int	getin(int ac)
{
	char	*c;
	char	*pro;

	(void)ac;
	pro = prompt();
	c = readline(pro);
	free(pro);
	if (c && *c)
		doit2(c);
	if (!c)
		return (0);
	if ((*c != ' ' || ft_strlen(c) > 1) && *c != '\n')
		add_history(c);
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
	go(ac, av);
	return (0);
}
