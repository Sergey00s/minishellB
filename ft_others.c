#include "ms.h"

int		ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

int strcmp_abs(const char *s1, const char *s2)
{
    int i;

    if (!s1 || !s2)
        return (-1);
    if (ft_strlen(s1) > ft_strlen(s2))
        return (1);
    else if (ft_strlen(s2) > ft_strlen(s1))
        return (2);
    i = 0;
    while (s1[i])
    {
        if (s1[i] > s2[i])
            return (1);
        if (s1[i] < s2[i])
            return (1);
        i++;
    }
    return (0);      
}