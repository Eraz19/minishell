#include "reader_.h"
#include "sig.h"
#include <unistd.h>
#include <errno.h>

int	reader_rl_getc(FILE *stream)
{
	unsigned char	c;
	ssize_t			n;

	(void)stream;
	while (true)
	{
		n = read(STDIN_FILENO, &c, 1);
		if (n == 1)
			return ((int)c);
		else if (n == 0)
			return (EOF);
		else if (errno == EINTR)
		{
			if (sig_int_is_pending())
				return (EOF);
			continue ;
		}
		return (EOF);
	}
}
