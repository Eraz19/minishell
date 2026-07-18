#include <pwd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include "libft.h"
#include "posix_helpers.h"

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

static t_error	ft_pw_slurp(char **out)
{
	int			fd;
	t_error		err;
	t_string	content;

	err = posix_open("/etc/passwd", O_RDONLY, &fd);
	if (err.type)
		return (err);
	err = posix_read_all(fd, &content);
	if (err.type)
		return (error_priorize(err, posix_close_if_open(fd)));
	*out = content.data;
	return (posix_close_if_open(fd));
}

t_error	ft_getpwnam(const char *name, struct passwd **out_pw)
{
	static struct passwd	pw;
	static char				*buf;
	char					*line;
	char					*next;
	t_error					err;

	*out_pw = NULL;
	if (name == NULL)
		return (error(ERR_NO));
	free(buf);
	buf = NULL;
	err = ft_pw_slurp(&buf);
	if (err.type)
		return (err);
	line = buf;
	while (*line)
	{
		next = line;
		while (*next && *next != '\n')
			next++;
		if (*next == '\n')
			*next++ = '\0';
		if (ft_pw_split(line, &pw, name))
			return (*out_pw = &pw, error(ERR_NO));
		line = next;
	}
	return (error(ERR_NO));
}
