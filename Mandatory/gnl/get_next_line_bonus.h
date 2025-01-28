/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:25:43 by mel-adna          #+#    #+#             */
/*   Updated: 2025/01/26 10:41:11 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

char	*get_next_line(int fd);
char	*readline(int fd, char *rest);
void	free_str(char **str);
char	*extract_line(char *rest);
char	*up_rest(char **rest);
int		gnl_strchr(const char *s, int c);
size_t	gnl_strlen(const char *s);
size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_strdup(const char *s);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

#endif