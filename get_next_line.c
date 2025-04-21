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

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 100

typedef struct	s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;

int		ft_foundnew(t_list	*lst)
{
	int i;

	while(lst)	
	{
		i = -1;
		while(lst->str[++i])
			if(lst->str[i] == '\n')
				return (1);	 
		lst = lst->next;
	}
	return (0);
}

char	*ft_strcnpy(t_list *lst, char *dest)
{
	int 	i;
	char	*src;

	i = -1;
	while(lst)
	{
		src = lst->str;
		while(*src)
		{
			if(*src == '\n')
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

int	ft_newlen(char *str)
{
	int i;
	
	i  = 0;
	while (*str && *str != '\n' && ++i)
		str++;
	return (i);
}

int	ft_strlen(char *s)
{
	int i;

	i = 0;
	while(*s && ++i)
		s++;
	return (i);
}

int	ft_linelen(t_list	*lst)
{
	int	i;
	
	i = 0;
	while(lst)
	{
		i += ft_newlen(lst->str);
		lst = lst->next;
	}
	return (i);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL); 
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_back(t_list **lst, char *str)
{
	t_list	*new;
	t_list	*last;

	last = ft_lstlast(*lst);	
	new	= (t_list *)malloc(sizeof(t_list));
	if (!new)
		return ;
	if (!last)
		*lst = new;
	else
		last->next = new;
	new->str = str;
	new->next = NULL;
}

void	get_list(t_list **dest, int fd)
{
	int		rd;
	char	*buffer;
	
	while(!ft_foundnew(*dest))
	{
		buffer = malloc(BUFFER_SIZE + 1);	
		rd = read(fd, buffer, BUFFER_SIZE);
		if (!rd)
		{	
			free(buffer);
			return ;
		}
		ft_add_back(dest, buffer);	
	}
}

char	*get_line(t_list *lst)
{
	int		linelen;
	char	*ret;

	linelen = ft_linelen(lst);
	ret = (char *)malloc(linelen + 1);
	
	ft_strcnpy(lst, ret);

	return (ret);
}

void	ft_freelist(t_list **lst, t_list *to_replace)
{
	t_list	*next;
	if (!lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->str);
		free(*lst);
		*lst = next;
	}
	if(to_replace)
		*lst = to_replace;
	else
		*lst = NULL;
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
	trimmed = (char *)malloc(ft_strlen(last->str) - i); 
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
		sleep(1);
	}
}
