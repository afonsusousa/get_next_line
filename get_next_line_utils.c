/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:57:37 by amagno-r          #+#    #+#             */
/*   Updated: 2025/04/20 20:34:10 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>

char	*ft_strcnpy(t_list *lst, char *dest, int fd)
{
	int		i;
	char	*src;

	i = -1;
	while (lst)
	{
		src = lst->str;
		while (*src && lst->fd == fd)
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

t_list	*ft_lstlast(t_list *lst, int fd)
{
	t_list	*last_occurence;

	last_occurence = NULL;
	if (!lst)
		return (NULL);
	if (!lst->next && lst->fd == fd)
		return (lst);
	while (lst)
	{
		if (lst->fd == fd)
			last_occurence = lst;
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (last_occurence);
}

void	ft_add_back(t_list **lst, char *str, int fd)
{
	t_list	*new;
	t_list	*last;

	last = *lst;
	while (last && last->next)
		last = last->next;
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return ;
	if (!last)
		*lst = new;
	else
		last->next = new;
	new->fd = fd;
	new->str = str;
	new->next = NULL;
}

t_list	*ft_lstnew(char *str, int fd)
{
	t_list	*ret;

	ret = (t_list *)malloc(sizeof(t_list));
	if (!ret)
		return (NULL);
	ret->fd = fd;
	ret->str = str;
	ret->next = NULL;
	return (ret);
}

void	ft_freelist(t_list **begin_list, t_list *preserve, int fd)
{
	t_list	*tmp;

	if (begin_list == NULL)
		return ;
	if (*begin_list == NULL)
	{
		if (preserve->str[0] && preserve->fd == fd)
			*begin_list = preserve;
		else
		{
			free(preserve->str);
			free(preserve);
		}
		return ;
	}
	if ((*begin_list)->fd == fd)
	{
		tmp = *begin_list;
		*begin_list = (*begin_list)->next;
		free(tmp->str);
		free(tmp);
		ft_freelist(begin_list, preserve, fd);
	}
	else
		ft_freelist(&((*begin_list)->next), preserve, fd);
}
