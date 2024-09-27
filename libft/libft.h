/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:51:51 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/28 00:20:37 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <stdarg.h>
# include "gnl/get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_printf
{
	char	*str;
	size_t	write_count;
	size_t	index;
	size_t	size;
	size_t	size_added_str;
	int		err;
}	t_printf;

/*-------------------------------------------------------------------------*/
/*								FT_PRINTF									*/
/*-------------------------------------------------------------------------*/
size_t		ft_wordcount_delimiter(const char *s, char delimiter);
void		ft_printf_init(t_printf *s);
void		ft_printf_realloc(t_printf *s);
void		ft_add_to_struct(t_printf *s, int c);
void		ft_print_char(t_printf *s, int c);
void		ft_print_str(t_printf *s, char *str);
void		ft_print_num_base(
				t_printf *s,
				long long n,
				int base,
				char *lst_base);
void		ft_print_ptr(t_printf *s, unsigned long long ptr);
void		ft_print_format(t_printf *s, char specifier, va_list ap);
int			ft_printf(const char *format, ...);
int			ft_printf_fd(int fd, const char *format, ...);
/*-------------------------------------------------------------------------*/
/*								IS											*/
/*-------------------------------------------------------------------------*/

int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
/*-------------------------------------------------------------------------*/
/*								MEMORY										*/
/*-------------------------------------------------------------------------*/

void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strdup(const char *s);

/*-------------------------------------------------------------------------*/
/*								STRING										*/
/*-------------------------------------------------------------------------*/

size_t		ft_strlcpy(char *dst, const char *src, size_t dst_len);
size_t		ft_strlen(const char *str);
size_t		ft_strlcat(char *dst, const char *src, size_t new_dst_len);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(const char *s1, const char *set);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

/*-------------------------------------------------------------------------*/
/*								SPLIT										*/
/*-------------------------------------------------------------------------*/

void		ft_skip_strchr(char **s, char delimiter);
const char	*ft_skip_quote(const char **s);
char		**ft_split(char const *s, char delimiter);
char		**ft_split_esc(const char *s, char delimiter);
void		*ft_memcpy_esc(void	*dst, void const *src, size_t n);
/*-------------------------------------------------------------------------*/
/*								TYPE										*/
/*-------------------------------------------------------------------------*/
int			ft_abs(int value);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
long double	ft_atold(const char *s);
/*-------------------------------------------------------------------------*/
/*						DYNAMIC MEMORY ALLOCATION							*/
/*-------------------------------------------------------------------------*/

void		*ft_calloc(size_t count, size_t size);

/*-------------------------------------------------------------------------*/
/*							FUNCTIONS										*/
/*-------------------------------------------------------------------------*/

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));

/*-------------------------------------------------------------------------*/
/*								FILES										*/
/*-------------------------------------------------------------------------*/

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/*-------------------------------------------------------------------------*/
/*								BONUS										*/
/*-------------------------------------------------------------------------*/
int			ft_lstsize(t_list *lst);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*-------------------------------------------------------------------------*/
/*								FREE										*/
/*-------------------------------------------------------------------------*/

void		ft_free_null(char **str);
int			ft_free_null_ret(char **str, int value);
void		ft_multi_free_null(char ***str);
int			ft_multi_free_null_ret(char ***str, int value);

/*-------------------------------------------------------------------------*/
/*							READLINE										*/
/*-------------------------------------------------------------------------*/
char		*ft_readline(int fd);

#endif