#include "ms.h"

int is_token(char *token)
{
    char    *tokens;
    char    **tokenlist;
    int     i;

    if (!token)
        return 0;
    tokens = "| > >> < <<";
    tokenlist = ft_split(tokens, ' ');
    i = 0;
    while (tokenlist[i])
    {
        if (!strcmp_abs(token, tokenlist[i]))
        {
            //free tokenlist;
            if (i == 0)
                return 2;
            return 1;
        }
        i++;
    }
    i = 0;
    //free tokenlist 
    return 0;
}

int iterate_till(char *str, int start, int c)
{
    while (str && str[start] && str[start] != c)
        start++;
    return start;
}

char *put_expand(char *str, int index)
{
    char *rtn;
    int     i;
    int     j;

    if (index < 1)
        return 0;
    rtn = ft_calloc(ft_strlen(str) + 2, sizeof(char));
    i = -1;
    while (++i <= index)
        rtn[i] = str[i];
    rtn[i] = ' ';
    j = i;
    i++;
    while (str[j])
    {
        rtn[i] = str[j];
        i++;
        j++;
    }
    return rtn;
}

void    change_it(char **arg, int *i, int index)
{
    char *temp;

    temp = *arg;
    *arg = put_expand(*arg, index);
    *i = 0;
    free(temp);
}

static void next_of(char *arg, int *i, char c)
{
    (*i)++;
    while (arg[*i] && arg[*i] != c)
            (*i)++;
    (*i)++;
}

char *redo(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (arg[i] == '"')
        {
            next_of(arg, &i, '"');
            continue;
        }
        if (arg[i] == 39)
        {
            next_of(arg, &i, 39);
            continue;
        }
        if (i > 0 && is_token_char(arg[i]) && (!is_token_char(arg[i - 1]) || arg[i - 1] == '|') && arg[i - 1] != ' ')
            change_it(&arg, &i, i - 1);
        else if (is_token_char(arg[i]) && (!is_token_char(arg[i + 1]) || arg[i + 1] == '|') && arg[i + 1] != ' ')
            change_it(&arg, &i, i);
        else
            i++;
    }
    return arg;
}

void redo_first(char **arg)
{
    char    *temp;

    temp = *arg;
    *arg = redo(*arg);
    //free(temp);
}

char	*removespace(char *str, int i, int x)
{
    char    *arg;

    arg = ft_strdup(str);
	if (!pre_control(arg, ft_strlen(arg)))
		error_exit(-1);
	while (arg[i])
	{   
		//fix_pre_parse(isspclpar(arg[i], arg[i + 1]), &arg, i + 1);
		// fix_post_parse(isspclpar2(arg, i), &arg, i - 1);
		if (ft_isspace(arg[i]))
        {
            arg[i] = ' ';
			cut_spaces(&arg, i + 1);
        }
		if (arg[i] == '"')
        {
            i++;
			i = iterate_till(arg, i, '"');
        }
		if (arg[i] == '\'')
        {
            i++;
			i = iterate_till(arg, ++i, '\'');
        }
		i += (arg[i] != 0);
	}
    redo_first(&arg);
	//fit_quto(&arg, x);
	fit_env_var(&arg);
	return (arg);
}

int is_token_char(int c)
{
    if (c == '>' || c == '<')
        return 1;
    if (c == '|')
        return 2;
    return 0;
}

int check_tokens(char **lst)
{
    int i;
    int temp;
    
    i = 0;
    while (lst[i])
    {
        if (is_token_char(lst[i][0]) && !is_token(lst[i]))
        {
            printf("1 %s -> %s \n", lst[i], lst[i + 1]);
            return (0);
        }
        if (is_token(lst[i]) && !lst[i + 1])
        {
            printf("2 %s -> %s \n", lst[i], lst[i + 1]);
            return (0);
        }
        temp = is_token(lst[i]);
        if (temp != 2 && temp && is_token(lst[i + 1]))
        {
            printf("3 %s -> %s \n", lst[i], lst[i + 1]);
            //freelst
            return (0);
        }
        i++;
    }
    return 1;
}

int findindex(char *str, char c)
{
    int i;

    i = 0;
    while (str && str[i] && str[i] != c)
        i++;
    return i;
}

void    fix_quote(char **lst)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (lst[i])
    {
        j = 0;
        while (lst[i][j] && is_token(lst[i]))
        {
            if (lst[i][j] == '"')
            {   
                ft_memmove(&lst[i][j], &lst[i][j + 1], ft_strlen(&lst[i][j]));
                j += findindex(&lst[i][j], '"');
                ft_memmove(&lst[i][j], &lst[i][j + 1], ft_strlen(&lst[i][j]));
                continue;
            }
            if (lst[i][j] == 39)
            {   
                ft_memmove(&lst[i][j], &lst[i][j + 1], ft_strlen(&lst[i][j]));
                j += findindex(&lst[i][j], 39);
                ft_memmove(&lst[i][j], &lst[i][j + 1], ft_strlen(&lst[i][j]));
                continue;
            }
            j++;
        }
        i++;
    }
}

char **pre_parse(char *str)
{
    char *arg;
    char **pre_parsed;

    arg = removespace(str, 0, 0);
    pre_parsed = specialsplit(arg, ' ');
    free(arg);
    if(!check_tokens(pre_parsed))
        //freelst
        exit(0);
    fix_quote(pre_parsed);
    return pre_parsed;
}
