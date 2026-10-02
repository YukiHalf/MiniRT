#include "parser.h"
# include <fcntl.h>
# include <unistd.h>

# define READ_SIZE 4096

static char	*append(char *old, size_t old_len, char *buf, size_t n)
{
	char	*new_buf;

	new_buf = malloc(old_len + n + 1);
	if (!new_buf)
	{
		free(old);
		return (NULL);
	}
	ft_memcpy(new_buf, old, old_len);
	ft_memcpy(new_buf + old_len, buf, n);
	new_buf[old_len + n] = '\0';
	free(old);
	return (new_buf);
}

static char	*read_all(int fd)
{
	char	buf[READ_SIZE];
	char	*all;
	size_t	len;
	ssize_t	bytes_read;

	all = malloc(1);
	if (!all)
		return (NULL);
	all[0] = '\0';
	len = 0;
	bytes_read = read(fd, buf, READ_SIZE);
	while (bytes_read > 0)
	{
		all = append(all, len, buf, (size_t)bytes_read);
		if (!all)
			return (NULL);
		len += (size_t)bytes_read;
		bytes_read = read(fd, buf, READ_SIZE);
	}
	if (bytes_read < 0)
	{
		free(all);
		return (NULL);
	}
	return (all);
}

char	*read_file(const char *path)
{
	int	fd;
	char	*all;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	all = read_all(fd);
	close(fd);
	return (all);
}
