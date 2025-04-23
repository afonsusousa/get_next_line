#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE 
#define BUFFER_SIZE 10
#endif
typedef struct	s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;

char    *ft_strcnpy(t_list *lst, char *dest);
int     ft_newlen(char *str);
t_list  *ft_lstlast(t_list *lst);
void    ft_add_back(t_list **lst, char *str);
void    ft_freelist(t_list **lst, t_list *to_replace);
int     ft_foundnew(t_list *lst);
void    get_list(t_list **dest, int fd);
char    *serve_line(t_list *lst);
void    clean_list(t_list **lst);
char    *get_next_line(int fd);

#endif
