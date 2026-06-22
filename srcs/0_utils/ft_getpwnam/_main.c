#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include "libft.h"

static void	ft_pw_fill(struct passwd *pw, char **field)
{
	pw->pw_name = field[0];
	pw->pw_passwd = field[1];
	pw->pw_uid = (uid_t)ft_atoi(field[2]);
	pw->pw_gid = (gid_t)ft_atoi(field[3]);
	pw->pw_gecos = field[4];
	pw->pw_dir = field[5];
	pw->pw_shell = field[6];
}

static int	ft_pw_split(char *line, struct passwd *pw, const char *name)
{
	int		i;
	int		f;
	char	*field[7];

	f = 0;
	i = 0;
	field[f++] = line;
	while (line[i] && f < 7)
	{
		if (line[i] == ':')
		{
			line[i] = '\0';
			field[f++] = line + i + 1;
		}
		i++;
	}
	if (f < 7 || str_cmp(field[0], name) != 0)
		return (0);
	return (ft_pw_fill(pw, field), 1);
}

static ssize_t	ft_pw_slurp(char *buf, size_t cap)
{
	int		fd;
	ssize_t	n;
	ssize_t	total;

	fd = open("/etc/passwd", O_RDONLY);
	if (fd < 0)
		return (-1);
	total = 0;
	n = read(fd, buf + total, cap - 1 - (size_t)total);
	while (n > 0)
	{
		total += n;
		n = read(fd, buf + total, cap - 1 - (size_t)total);
	}
	close(fd);
	if (n < 0)
		return (-1);
	return (buf[total] = '\0', total);
}

struct passwd	*ft_getpwnam(const char *name)
{
	static struct passwd	pw;
	static char				buf[65536];
	char					*line;
	char					*next;

	if (name == NULL || ft_pw_slurp(buf, sizeof(buf)) < 0)
		return (NULL);
	line = buf;
	while (*line)
	{
		next = line;
		while (*next && *next != '\n')
			next++;
		if (*next == '\n')
			*next++ = '\0';
		if (ft_pw_split(line, &pw, name))
			return (&pw);
		line = next;
	}
	return (NULL);
}
