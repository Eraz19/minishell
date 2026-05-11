#ifndef ASM_STUBS_H
# define ASM_STUBS_H

# include "error.h"
# include <unistd.h>

pid_t	ft_getpid(void);
pid_t	ft_getppid(void);
// ERR_NO / ERR_UNABLE_TO_BLOCK_STDIN
t_error	ft_stdin_set_blocking(void);

#endif
