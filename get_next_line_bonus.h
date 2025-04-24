/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:57:37 by amagno-r          #+#    #+#             */
/*   Updated: 2025/04/20 20:34:10 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	int				fd;
	char			*str;
	struct s_list	*next;
}	t_list;

char	*ft_strcnpy(t_list *lst, char *dest, int fd);
t_list	*ft_lstnew(char *str, int fd);
t_list	*ft_lstlast(t_list *lst, int fd);
void	ft_add_back(t_list **lst, char *str, int fd);
void	ft_freelist(t_list **lst, t_list *preserve, int fd);
int		ft_foundnew(t_list *lst, int fd);
void	get_list(t_list **dest, int fd);
char	*serve_line(t_list *lst, int fd);
void	clean_list(t_list **lst, int fd);
char	*get_next_line(int fd);

#endif
