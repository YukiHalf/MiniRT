/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 13:15:22 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 13:15:24 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>
#include <unistd.h>

static void	drain(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

static void	strip_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\r')
		line[len - 1] = '\0';
}

static const char	*read_lines(int fd, t_line_fn fn, void *ctx, int *n)
{
	char		*line;
	const char	*err;

	line = get_next_line(fd);
	while (line)
	{
		(*n)++;
		strip_newline(line);
		err = fn(ctx, line);
		free(line);
		if (err)
			return (err);
		line = get_next_line(fd);
	}
	return (NULL);
}

const char	*read_scene_file(const char *path, t_line_fn fn, void *ctx, int *ln)
{
	int			fd;
	int			n;
	const char	*err;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ("cannot read the scene file");
	n = 0;
	err = read_lines(fd, fn, ctx, &n);
	*ln = n;
	if (err)
		drain(fd);
	close(fd);
	return (err);
}
