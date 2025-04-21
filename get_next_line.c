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
		if (rd <= 0)
		{
			if (rd == 0 && *dest)
				return ;
			if (rd == -1)
			{
				free(buffer);
				ft_freelist(dest, NULL);
				return ;
			}
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
	t_list	*clean;
	int		i;
	int		j;
	char	*trimmed;


	clean = (t_list *)malloc(sizeof(t_list));
	last = ft_lstlast(*lst);
	if(!last)
		return ;
	j = -1;
	i = ft_newlen(last->str);
	trimmed = (char *)malloc(BUFFER_SIZE - i + 2); 
	while(last->str[++i])
		trimmed[++j] = last->str[i];
	trimmed[++j] = '\0';
	clean->str = trimmed;
	clean->next = NULL;
	ft_freelist(lst, clean);
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
		printf("%s", line);
		free(line);
	}
	free(line);
	close(file);
}
