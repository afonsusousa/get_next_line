#include "get_next_line.h"

#include <stdlib.h>

char *ft_strcnpy(t_list *lst, char *dest)
{
	int i;
	char *src;

	i = -1;
	while (lst)
	{
		src = lst->str;
		while (*src)
		{
			if (*src == '\n')
			{
				dest[++i] = '\n';
				dest[++i] = '\0';
				return (dest);
			}
			dest[++i] = *src++;
		}
		lst = lst->next;
	}
	dest[++i] = '\0';
	return (dest);
}

int ft_newlen(char *str)
{
	int i;

	i = 0;
	while (*str && *str != '\n' && ++i)
		str++;
	return (i);
}

t_list *ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void ft_add_back(t_list **lst, char *str)
{
	t_list *new;
	t_list *last;

	last = ft_lstlast(*lst);
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return;
	if (!last)
		*lst = new;
	else
		last->next = new;
	new->str = str;
	new->next = NULL;
}

void ft_freelist(t_list **lst, t_list *last)
{
	t_list *next;
	if (!lst)
		return;
	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->str);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
	if(last->str[0])
		*lst = last;
	else
	{
		free(last->str);
		free(last);
	}
}