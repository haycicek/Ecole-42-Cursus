/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 02:26:06 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>

// LIBFT
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2, int total_len);
char		**free_malloc(char **tab, size_t i);
int			word_count(char const *s, char c);
char		**ft_split(char const *s, char c);
void		ft_putstr_fd(char *s, int fd);
int			ft_strcmp(char *s1, char *s2);
void		*ft_calloc(size_t count, size_t size);
char		*ft_itoa(int n);
int			ft_atoi(const char *str);
int			ft_isalnum(int c);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strcat(char *dest, char *src);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *s, int c, size_t n);
char		*ft_strstr(char *big, char *little);
#endif
