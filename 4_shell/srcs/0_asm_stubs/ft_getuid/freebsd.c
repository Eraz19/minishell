#if defined(__FreeBSD__)
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>

static int	ft_skip_field(const char *string, int index)
{
	while (string[index] && string[index] != ' '
		&& string[index] != '\t' && string[index] != '\n')
		index++;
	while (string[index] == ' ' || string[index] == '\t')
		index++;
	return (index);
}

static uid_t	ft_parse_uid(const char *string)
{
	unsigned long	uid;
	int				index;
	int				field;

	index = 0;
	field = 0;
	while (field < 12 && string[index])
	{
		index = ft_skip_field(string, index);
		field++;
	}
	if (field != 12 || string[index] < '0' || string[index] > '9')
		return ((uid_t)-1);
	uid = 0;
	while (string[index] >= '0' && string[index] <= '9')
	{
		uid = (uid * 10) + (unsigned long)(string[index] - '0');
		index++;
	}
	return ((uid_t)uid);
}

static uid_t	ft_read_uid_file(const char *path)
{
	char	buf[512];
	int		fd;
	ssize_t	nread;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ((uid_t)-1);
	nread = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (nread <= 0)
		return ((uid_t)-1);
	buf[nread] = '\0';
	return (ft_parse_uid(buf));
}

uid_t	ft_getuid(void)
{
	uid_t	uid;

	uid = ft_read_uid_file("/proc/curproc/status");
	if (uid != (uid_t)-1)
		return (uid);
	return (ft_read_uid_file("/proc/self/status"));
}

#endif
