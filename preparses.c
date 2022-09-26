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

char	*removespace(char *str, int i, int x)
{
    char    *arg;

    arg = ft_strdup(str);
	while (arg[i])
	{   
		fix_pre_parse(isspclpar(arg[i], arg[i + 1]), &arg, i + 1);
		fix_post_parse(isspclpar2(arg, i), &arg, i - 1);
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
	if (!pre_control(arg, ft_strlen(arg)))
		error_exit(-1);
	//fit_quto(&arg, x);
	fit_env_var(&arg);
	return (arg);
}

int is_token_char(int c)
{
    if (c == '|' || c == '>' || c == '<')
        return 1;
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
    printf("arg %s \n", arg);
    exit(1);
    pre_parsed = specialsplit(arg, ' ');
    free(arg);
    if(!check_tokens(pre_parsed))
        //freelst
        exit(0);
    fix_quote(pre_parsed);
    return pre_parsed;
}
