/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:42:11 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/22 20:25:39 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	*prompt(void)
{
	char	*str;
	char	*ret;

	str = getcwd(0, 0);
	ret = ft_strjoin(str, " +++ mimiShell -> ");
	free(str);
	return (ret);
}

void	sig_handler(int signum)
{	
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	go(int ac, char **av)
{
	(void)av;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (getin(ac))
	{
		(void)0;
	}
	return (1);
}

char	**putmenv(char **env)
{
	char	**rtn;
	int		len;
	int		i;

	i = -1;
	len = lenof(env);
	rtn = malloc((len + 1) * sizeof(char *));
	while (++i < len)
		rtn[i] = ft_strdup(env[i]);
	rtn[i] = 0;
	return (rtn);
}
