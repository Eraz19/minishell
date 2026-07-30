#if defined(__linux__)
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>

static int	ft_is_uid_field(const char *string, int index)
{
	return ((index == 0 || string[index - 1] == '\n')
		&& string[index] == 'U'
		&& string[index + 1] == 'i'
		&& string[index + 2] == 'd'
		&& string[index + 3] == ':');
}

static int	ft_skip_number(const char *string, int index)
{
	while (string[index] >= '0' && string[index] <= '9')
		index++;
	while (string[index] == ' ' || string[index] == '\t')
		index++;
	return (index);
}

static uid_t	ft_parse_euid(const char *string)
{
	unsigned long	euid;
	int				index;

	index = 0;
	while (string[index])
	{
		if (ft_is_uid_field(string, index))
		{
			index += 4;
			while (string[index] == ' ' || string[index] == '\t')
				index++;
			if (string[index] < '0' || string[index] > '9')
				return ((uid_t)-1);
			index = ft_skip_number(string, index);
			if (string[index] < '0' || string[index] > '9')
				return ((uid_t)-1);
			euid = 0;
			while (string[index] >= '0' && string[index] <= '9')
			{
				euid = (euid * 10)
					+ (unsigned long)(string[index] - '0');
				index++;
			}
			return ((uid_t)euid);
		}
		index++;
	}
	return ((uid_t)-1);
}

uid_t	ft_geteuid(void)
{
	char	buf[4096];
	int		fd;
	ssize_t	nread;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd < 0)
		return ((uid_t)-1);
	nread = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (nread <= 0)
		return ((uid_t)-1);
	buf[nread] = '\0';
	return (ft_parse_euid(buf));
}

#endif
