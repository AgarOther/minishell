/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:21:22 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/08 00:42:20 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include "ft_printf/includes/ft_printf.h"

typedef struct s_list
{
	char			*str;
	char			**sptstr;
	struct s_list	*next;
}					t_list;

int			ft_atoi(const char *nptr);
long long	ft_atol(const char *nptr);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_hasdigit(char *str);
int			ft_isalnum(int c);
int			ft_stralnum(char *str);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
int			ft_is_eol(char *str);
int			ft_isfilled(char *str, int c, char *whitelist);
int			ft_istrimmable(char *str, int c);
void		*ft_realloc(void *old, int old_size, int new_size);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
char		*ft_strcat(char *dst, char *src);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
size_t		ft_tablen(char **s);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strlencmp(const char *s1, const char *s2, int s2_crop);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strcrop(char *src, int to_crop);
int			ft_strhasquote(char *str);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		**ft_splitfirst(char *s, char c);
char		**ft_split_quote(char const *s, char c);
int			ft_intlen(int n);
int			ft_countsplits(const char *str, char c);
int			ft_countsplits_quote(const char *str, char c);
int			ft_countwords(const char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_free(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
int			ft_stroccur(char *str, int c);
int			ft_strcharindex(char *str, char c);
int			ft_strstartswith(const char *str, const char *cmp_str);
int			ft_strcontains(char *s1, char *s2);
char		*ft_strquote(char *str, char quote, char index1, char index2);
int			ft_stratoiable(char *str);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_tabfree(char **tab, int size);
void		ft_tabprint(char **tab, int endl);
int			ft_tabhasemptystr(char **tab);
char		**ft_tabdup(char **tab, int size);
void		ft_lstprint(t_list *lst, int endl);
t_list		*ft_lstnew(char *new );
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst);
void		ft_lstclear(t_list **lst);
char		**ft_splitfirst(char *str, char c);
#endif
