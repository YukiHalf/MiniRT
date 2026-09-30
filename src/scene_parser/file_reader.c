#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
 
#define READ_SIZE 4096
 
static char	*append(char *old, size_t old_len, char *buf, size_t n)
{
	char	*new;
 
	new = malloc(old_len + n + 1);
	if (!new)
	{
		free(old);
		return (NULL);
	}
	ft_memcpy(new, old, old_len);
	ft_memcpy(new + old_len, buf, n);
	new[old_len + n] = '\0';
	free(old);
	return (new);
}
 
static char	*read_all(int fd)
{
	char	buf[READ_SIZE];
	char	*all;
	size_t	len;
	ssize_t	n;
 
	all = malloc(1);
	if (!all)
		return (NULL);
	all[0] = '\0';
	len = 0;
	n = read(fd, buf, READ_SIZE);
	while (n > 0)
	{
		all = append(all, len, buf, n);
		if (!all)
			return (NULL);
		len += n;
		n = read(fd, buf, READ_SIZE);
	}
	if (n >= 0 && ft_strlen(all) == len)
		return (all);
	free(all);
	return (NULL);
}
 
char	*read_file(const char *path)
{
	int		fd;
	char	*all;
 
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	all = read_all(fd);
	close(fd);
	return (all);
}
