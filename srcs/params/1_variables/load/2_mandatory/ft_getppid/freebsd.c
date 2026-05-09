#if defined(__FreeBSD__)
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

static int	ft_parse_ppid(const char *s)
{
	int	i;
	int	ppid;

	i = 0;
	i = ft_skip_field(s, i);
	i = ft_skip_field(s, i);
	if (s[i] < '0' || s[i] > '9')
		return (-1);
	ppid = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		ppid = (ppid * 10) + (s[i] - '0');
		i++;
	}
	return (ppid);
}

static int	ft_read_ppid_file(const char *path)
{
	char	buf[512];
	int		fd;
	ssize_t	nread;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	nread = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (nread <= 0)
		return (-1);
	buf[nread] = '\0';
	return (ft_parse_ppid(buf));
}

int	ft_getppid(void)
{
	int	ppid;

	ppid = ft_read_ppid_file("/proc/curproc/status");
	if (ppid != -1)
		return (ppid);
	return (ft_read_ppid_file("/proc/self/status"));
}

#endif
