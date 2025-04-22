/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:57:37 by amagno-r          #+#    #+#             */
/*   Updated: 2025/04/20 20:34:10 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int ft_foundnew(t_list *lst)
{
	int i;

	while (lst)
	{
		i = -1;
		while (lst->str[++i])
			if (lst->str[i] == '\n')
				return (1);
		lst = lst->next;
	}
	return (0);
}

void	get_list(t_list **dest, int fd)
{
	int		rd;
	char	*buffer;

	while(!ft_foundnew(*dest))
	{
		buffer = malloc(BUFFER_SIZE + 1);	
		if(!buffer)
			return ;
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == 0)
		{
			free(buffer);
			return ;
		}
		if (rd == -1)
		{
			free(buffer);
			ft_freelist(dest, NULL);
			return ;
		}
		
		buffer[rd] = '\0';
		ft_add_back(dest, buffer);	
	}
}

char	*get_line(t_list *lst)
{
	int		linelen;
	t_list	*iter;
	char	*ret;

	linelen = 0;
	iter = lst;
	if(!iter)
		return (NULL);
	while(iter)
	{
		linelen += ft_newlen(iter->str);
		iter = iter->next;
	}
	ret = (char *)malloc(linelen + 2);
	ft_strcnpy(lst, ret);
	return (ret);
}

void	clean_list(t_list **lst)
{
	t_list	*last;
	int		i;
	int		j;

	last = ft_lstlast(*lst);
	if(!last)
		return ;
	j = -1;
	i = ft_newlen(last->str);
	if(!last->str[0])
	{
		ft_freelist(lst, NULL);
		return ;
	}
	ft_freelist(lst, last);
	while(last->str[++i])
		last->str[++j] = last->str[i];
	while(last->str[++j])
		last->str[j] = '\0';
}

char	*get_next_line(int fd)
{
	static t_list	*line = NULL;	
	char	*ret;

	get_list(&line, fd);

	ret = get_line(line);
	
	clean_list(&line);
	
	return (ret);
}

#include <stdio.h>
int main()
{
	int	file = open("test.txt", O_RDONLY);
	char *line;
	while(*(line = get_next_line(file)))
	{
		printf("%s\n", line);
		free(line);
	}
	free(line);
	close(file);
}
