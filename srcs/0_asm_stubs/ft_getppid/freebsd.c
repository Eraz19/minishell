#if defined(__FreeBSD__)
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>

static int	ft_skip_field(const char *s, int i)
{
	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
		i++;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (i);
}

static pid_t	ft_parse_ppid(const char *s)
{
	int		i;
	pid_t	ppid;

	i = 0;
	i = ft_skip_field(s, i);
	i = ft_skip_field(s, i);
	if (s[i] < '0' || s[i] > '9')
		return ((pid_t)-1);
	ppid = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		ppid = (ppid * 10) + (s[i] - '0');
		i++;
	}
	return (ppid);
}

static pid_t	ft_read_ppid_file(const char *path)
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
	return (ft_parse_ppid(buf));
}

pid_t	ft_getppid(void)
{
	pid_t	ppid;

	ppid = ft_read_ppid_file("/proc/curproc/status");
	if (ppid != (pid_t)-1)
		return (ppid);
	return (ft_read_ppid_file("/proc/self/status"));
}

#endif
