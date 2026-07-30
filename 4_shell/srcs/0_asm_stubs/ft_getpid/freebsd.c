#if defined(__FreeBSD__)
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>

static int	ft_skip_field(const char *string, int index)
{
	while (string[index] && string[index] != ' ' && string[index] != '\t'
		&& string[index] != '\n')
		index++;
	while (string[index] == ' ' || string[index] == '\t')
		index++;
	return (index);
}

static pid_t	ft_parse_pid(const char *string)
{
	int		index;
	pid_t	pid;

	index = 0;
	index = ft_skip_field(string, index);
	if (string[index] < '0' || string[index] > '9')
		return ((pid_t)-1);
	pid = 0;
	while (string[index] >= '0' && string[index] <= '9')
	{
		pid = (pid * 10) + (string[index] - '0');
		index++;
	}
	return (pid);
}

static pid_t	ft_read_pid_file(const char *path)
{
	char	buf[512];
	int		fd;
	ssize_t	nread;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ((pid_t)-1);
	nread = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (nread <= 0)
		return ((pid_t)-1);
	buf[nread] = '\0';
	return (ft_parse_pid(buf));
}

pid_t	ft_getpid(void)
{
	pid_t	pid;

	pid = ft_read_pid_file("/proc/curproc/status");
	if (pid != (pid_t)-1)
		return (pid);
	return (ft_read_pid_file("/proc/self/status"));
}

#endif
