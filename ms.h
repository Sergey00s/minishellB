/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:45:16 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/23 17:30:29 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# define DB 4
# define DR 3
# define PP 2
# define BDB 5
# define BDR 6

typedef struct s_stuff
{
	t_list	*parsed;
	char	**env;
	char	**args;
	char	**exports;
	int		checker;
	int		code;
}				t_stuff;

typedef struct s_char2d
{
	char	**lst;
	int		len;
	int		type;
	void	(*append)(struct s_char2d *self, char *value);
	char	*(*at)(struct s_char2d *self, int i);
	void	(*del)(struct s_char2d *self);
}				t_char2d;

typedef struct s_redir
{
	char			*file;
	char			*type;
	struct s_redir	*next;
	struct s_redir	*prev;
}				t_redir;

typedef struct s_parsed
{
	t_char2d	*args;
	t_redir		*redirs;
	int			input;
	int			output;
	int			dlm;
	int			fd[2];
	int			order;
	int			type;
	int			wr;
	int			bin;
}				t_parsed;

typedef struct s_vars
{
	int		i;
	int		len;
	char	*front;
	char	*end;
	char	*temp;
	char	*rtn;
	int		start;
	int		last;
}				t_vars;

extern t_stuff	*g_stuff;

int			checkorderof(char **parsed);
int			checkdquote(t_parsed *parsed);
int			checkredirs(t_parsed *parsed);
int			checkacces(char *temp);
int			checkorder(t_parsed *parsed);
int			checkifinq(char *str, int i);
int			check_parse(t_list *lst);
int			checkpipes(t_parsed *parsed);
int			checkquote(t_parsed *parsed);
int			check_build(char **args, t_parsed *parsed);
int			checkit(char *str);
int			ft_parse2(char *arg, int i, int len);
int			ft_isnot(char c);
int			ft_echo(char **args, t_parsed *parsed);
int			ft_myexport(char *value);
int			is_in(char *set, int c);
int			isspcl2(char *str);
int			isredir(char *str);
int			isspclpar(char a, char b);
int			isspclpar2(char *arg, int i);
int			isspcl(char *str);
int			is_ok(char c);
int			isspcl(char *str);
int			inquote(char *arg, int i);
int			lenof(char **l);
int			typeof2(char *str, int start, int end);
int			getin(int ac);
int			gosingle(t_parsed *parsed);
int			mystrcmp(const char *s1, const char *s2);
int			get_path(char *path, char **theway);
int			go(int ac, char **av);
int			pre_control(char *arg, int len);
int			sort_print(char **env);

char		*format(char *str, char *var, char *value, t_vars vars);
char		**specialsplit(char const *s, char c);
char		*ft_fenv_param(char **menv, char *var);
char		**ft_split(char const *str, char c);
char		*f_var_env(char **menv, char *var);
char		*find_envpath(char **env);
char		*check_write(t_parsed *parsed);
char		*check_owr(t_parsed *parsed);
char		*check_read(t_parsed *parsed);
char		*find_var_env(char **menv, char *var);
char		**putmenv(char **env);
char		*get_after(char *str, char c);
char		*get_till(char *str, char c);
char		*prompt(void);
char		*removespace(char *arg, int i, int j);
char		*ft_getenvparam(char *var);
char		*makeit(char *var, char *value);
char		*check_dlm(t_parsed *parsed);
char		**ft_parse(char *str, char sep, char **menv);
char		*ft_putit(const char *s1, char c);

void		tmp_next(t_redir **tmp, char **key);
void		delim_wr(int *pipes, char *buffer, t_parsed *parsed);
void		init_fd(t_parsed *parsed);
void		delim(t_parsed *parsed, char *line, char *key);
void		free_2d(char **env);
void		fit_new(t_parsed *new);
void		error_exit(int code);
void		ft_env2(void);
void		ft_redir_addback(t_redir **lst, t_redir *new);
void		str_print(t_parsed *self);
void		str_append(t_parsed **rtn, t_parsed *args);
void		ft_unset(char **args);
void		fit_ex(void);
void		ft_export(char **args);
void		ft_putchar(int c);
void		jump_spaces(char **str);
void		closepipes(t_list *parsed);
void		find_dollar_put(char **str);
void		ft_checklast(char **rtn, char *var, char *str);
void		ft_expand(char *str);
void		ft_toenv(char *var, char *value);
void		ft_toenv2(char *str);
void		cut_spaces(char **arg, int i);
void		sig_handler(int signum);
void		init_fd(t_parsed *parsed);
void		doit2(char *a);
void		free_parsed(t_parsed *parsed);
void		free_stuff(void);
void		do_next(t_list *parsed, t_parsed *temp);
void		run3(t_list *parsed);
void		put_new(char **arg, int pos);
void		fix_pre_parse(int code, char **arg, int pos);
void		put_new2(char **arg, int pos);
void		free_ex_env(void);
void		ft_myexpand(char *str);
void		ft_tomyenv(char *str);
void		ex_print(void);
void		move_to_right(char **arg, int i, int code);
void		movethem(char **arg, int i, int code);
void		fit_quto(char **arg, int x);
void		fit_env_var(char **arg);
void		fix_post_parse(int code, char **arg, int pos);
void		jump_till_not(char **str, char *set);
void		jump_till(char **str);
void		ft_parse2_while(t_char2d *temp, int len, int i, char **parsed);
void		put_them2(int start, int end, char **arg, int i);
void		fit_redir(t_redir *redir);
void		ft_fixit(t_redir *redir);

t_redir		*ft_redirlast(t_redir *lst);
t_redir		*ft_create(char *file, char *type);
t_char2d	*chararr(void);
t_parsed	*str_init(t_char2d *args);
t_parsed	*str_init(t_char2d *args);
#endif
