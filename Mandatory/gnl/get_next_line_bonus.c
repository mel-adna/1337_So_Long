/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:25:29 by mel-adna          #+#    #+#             */
/*   Updated: 2025/01/26 10:41:30 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

char	*up_rest(char **rest)
{
	char	*restline;
	int		index;

	index = gnl_strchr(*rest, '\n');
	if (index == -1)
		return (free_str(rest), NULL);
	index++;
	restline = malloc(gnl_strlen(*rest + index) + 1);
	if (!restline)
		return (free_str(rest), NULL);
	gnl_strlcpy(restline, *rest + index, gnl_strlen(*rest + index) + 1);
	free(*rest);
	*rest = restline;
	return (*rest);
}

char	*extract_line(char *rest)
{
	char	*line;
	int		i;
	int		index;

	index = gnl_strchr(rest, '\n');
	if (index != -1)
		i = index + 1;
	else
		i = gnl_strlen(rest);
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	gnl_strlcpy(line, rest, i + 1);
	return (line);
}

char	*readline(int fd, char *rest)
{
	char	*buff;
	char	*temp;
	ssize_t	nread;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (free(rest), NULL);
	nread = read(fd, buff, BUFFER_SIZE);
	while (nread > 0)
	{
		buff[nread] = '\0';
		temp = rest;
		rest = gnl_strjoin(rest, buff);
		free(temp);
		temp = NULL;
		if (!rest)
			return (free(temp), free(buff), NULL);
		if (gnl_strchr(buff, '\n') > -1)
			break ;
		nread = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest[OPEN_MAX];
	char		*strline;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (free_str(&rest[fd]), NULL);
	rest[fd] = readline(fd, rest[fd]);
	if (!rest[fd] || *rest[fd] == '\0')
		return (free_str(&rest[fd]), NULL);
	strline = extract_line(rest[fd]);
	if (!strline)
		return (free_str(&rest[fd]), NULL);
	if (!up_rest(&rest[fd]))
		return (free_str(&rest[fd]), strline);
	return (strline);
}
