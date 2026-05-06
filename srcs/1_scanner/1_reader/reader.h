#ifndef READER_H
# define READER_H

# include "libft.h"
# include <stdbool.h>

/*
Ce module est le SEUL à pouvoir intéragir avec l'input (stdin / file).
Les autres modules (lexer, parser...) peuvent le trigger lorsqu'ils ont besoin de récupérer une input.
*/

typedef enum e_reader_mode
{
	INTERACTIVE,
	NON_INTERACTIVE
}	t_reader_mode;

typedef struct s_reader
{
	bool			is_interactive;	// default: true
	const char		*input_path;	// default: NULL
	int				input_fd;		// default: STDIN_FILENO
}	t_reader;

// Content of `-` POSIX variable
typedef struct s_shell_options
{
	
}	t_shell_options;

void	reader_init(t_reader *reader);
void	reader_set_input_path(const char *path);

/*
1. Display prompt on stderr
2. Remove escaped newlines
3. Save input into dst
4. Update history (only in tty ??)
*/
bool	reader_get_line(const char *prompt, t_buff *dst);

#endif
