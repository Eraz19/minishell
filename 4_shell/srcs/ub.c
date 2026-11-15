/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ub.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 17:37:39 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 17:42:13 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "posix_helpers.h"
#include "shell.h"
#include <unistd.h>
#include <string.h>

#define COND_PREFIX	": warning: unspecified behaviour: "
#define IMPL_PREFIX	": implemented as: "
#define UB_SUFFIX	"\" 🤪\n ╰──▶ UNDEFINED BEHAVIOUR 💣\n"
#define LOOP_SUFFIX	" 😵‍💫\n ╰──▶ INFINITE LOOP 😵‍💫\n"

#define ASCII_XAV	"                                                  =..==-==\
                       \n\
                                                 -=-=-======-=+---             \
                             \n\
                                             -=======++++++--:.::-=::          \
                             \n\
                                          :==--=******#######*+-::-===         \
                             \n\
                                        .==-:+*######*###########*:-=+=        \
                             \n\
                                       .-+-=#####*#################=-#=--      \
                             \n\
                                      :==-*#%%%%#################%##+-=*=-     \
                             \n\
                                      -==+%%%%%%%##########*#####%%%%=-==*+-   \
                             \n\
                                     .==+#%%%%%%%#################%%%#+::-++-. \
                             \n\
                                    ===-+#%%%%%%%###########*****##%%#=:-:-=*= \
                             \n\
                                   :--:-=##%%%%###++++**#*+==----==+#%*:::-:==-\
                             \n\
                                  --=::-=*%%%#+=---=+=*###*++==++*#*#%%=-:-:=-:\
                             \n\
                                  ----=--#%%%+***-:::=+##*#====++***#%%#===-+=:\
                             \n\
                                  .=:::.-#%%%#+*#*+=++#%##*#*+==++*#%%%#+*=+=+:\
                             \n\
                                  :--=+--*%%%#%##***##%%%#**#*+***##%%%%*#=--- \
            +##%             \n\
                                   :--=#*+#%%%%%####++%%%#*###*-+**#%%%%**+-:  \
           =###@             \n\
                             ###*  .:--#+=##%#%%##*++****+=+=**+==**#%#%*#.-=: \
           ####%-            \n\
                       :%%%%#**++   ---#+=*#%%###*++*###*********+=+*##%#*-=:  \
           :##%%#            \n\
                     @%%%#*++++- ##*  -=*#*#####***#*###*++++=+*++++***##-==-  \
            #%#%%*           \n\
                    @%##=+#%%%%##**+  -=:#####*****+==::++-**+:.==+++**%:.:-=- \
            ##%#%%           \n\
                   @%%#%%%%##*=:      -=::.=*******+*##*+++++****+++****-:::   \
            :*#%#%%#         \n\
                   %%%%###+.         ::-:.:..**+*****###*+**+*****+++**+...    \
             +##%%#%         \n\
                 %%%%##*+*+           ::::....++++*****************+++=..      \
             ***###%%        \n\
                %%%%%#####%%###%%=.............=++++**********+***++++.......::\
:            **####%%%       \n\
               #%%%##########*++:...............+======++=+========++ .:.......\
.........:= #**#####%%       \n\
           ::.:%%%##*+****+......................-+=======-----====. ..........\
............****#####%%      \n\
          :::.*%%%####*******+...-**++++..... ......==----------:  .... .......\
..-***+...#*##########*:+    \n\
          ::.:%%%#####*+****########*****+:..  ......   ....     ...... .......\
++**#########**######%#=:#   \n\
        *:::.#%%%%#####**######***+=-........  ......          .......  .......\
:..:=+**#######*#%####%%=-#  \n\
        :::.=%%%%##***###*****+:  .........     ...                      ......\
........=**############%#:-  \n\
        ..:-%%%#**+******+++-... .........        .                     .......\
..........=+*#*####***##%%=  \n\
        ..*%%%##*******+-..    ... ......  .         .                  .......\
. ...........+*****++**###+:@\n\
        ..:%#######***-     ....... ........                            .......\
.. .... .... ..=****+*****-.:\n\
        :....-*******:       .. ....... ....                            .......\
.. ..   ...   . .#*####=.....\n\
        .....   .:++-          .............                            .......\
......       . . ......   ...\n"

void	print_unspecified_behaviour(
			const char *opt_prefix,
			const char *posix_citation,
			const char *implemented_as)
{
	const char	*shell_name;

	shell_name = shell_get_name();
	(void)posix_write(STDERR_FILENO, shell_name, str_len(shell_name));
	(void)posix_write(STDERR_FILENO, COND_PREFIX, str_len(COND_PREFIX));
	if (opt_prefix != NULL)
	{
		(void)posix_write(STDERR_FILENO, opt_prefix, str_len(opt_prefix));
		(void)posix_write(STDERR_FILENO, ": ", 2);
	}
	(void)posix_write(STDERR_FILENO, posix_citation, str_len(posix_citation));
	(void)posix_write(STDERR_FILENO, IMPL_PREFIX, str_len(IMPL_PREFIX));
	(void)posix_write(STDERR_FILENO, implemented_as, str_len(implemented_as));
	(void)posix_write(STDERR_FILENO, "\n", 1);
}

t_error	undefined_behaviour(const char *message)
{
	posix_write(STDERR_FILENO, ASCII_XAV, str_len(ASCII_XAV));
	(void)posix_write(STDERR_FILENO, "\"", 1);
	(void)posix_write(STDERR_FILENO, message, str_len(message));
	(void)posix_write(STDERR_FILENO, UB_SUFFIX, str_len(UB_SUFFIX));
	return (error_print(error(ERR_UB), NULL, NULL));
}

t_error	error_infinite_loop(void)
{
	posix_write(STDERR_FILENO, ASCII_XAV, str_len(ASCII_XAV));
	(void)posix_write(STDERR_FILENO, LOOP_SUFFIX, str_len(UB_SUFFIX));
	return (error(ERR_VEOF));
}
