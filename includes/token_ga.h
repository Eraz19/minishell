#ifndef TOKEN_GA_H
# define TOKEN_GA_H

# include "libft.h"
# include <stddef.h>

typedef enum e_token_category
{
	TOKEN_CAT_WORD,			// Program name, arguments, raw numbers for file descriptors...
	TOKEN_CAT_REDIRECTION,	// Data source / target (files / file descriptors)
	TOKEN_CAT_CONTROL		// If / when /how a command runs
}	t_token_category;

typedef enum e_token_type
{
	// Category: TOKEN_CAT_WORD
	TOKEN_WORD,				//		- [POSIX] Standard words (program names, arguments, filenames...)
	TOKEN_IO_NUMBER,		//		- [POSIX] Digit(s) (file descriptor) optionaly prefixing a redirection (the 2 in 2>)
	// Category: TOKEN_CAT_REDIRECTION
	TOKEN_REDIR_IN,			// <	- [POSIX] Redirects file to standard input
	TOKEN_REDIR_OUT,		// >	- [POSIX] Redirects standard output to a file (truncate)
	TOKEN_APPEND,			// >>	- [POSIX] Redirects standard output to a file (append)
	TOKEN_HEREDOC,			// <<	- [POSIX] Reads input until a delimiter string is reached
	TOKEN_REDIR_IN_OUT,		// <>	- [POSIX] Opens a file for both reading and writing
	TOKEN_DUP_IN,			// <&	- [POSIX] Duplicates an input file descriptor
	TOKEN_DUP_OUT,			// >&	- [POSIX] Duplicates an output file descriptor
	TOKEN_CLOBBER,			// >|	- [POSIX] Overwrites a file even if noclobber is on
	TOKEN_HEREDOC_STRIP,	// <<-	- [POSIX] Heredoc that strips leading tabs from the input
	TOKEN_HERE_STRING,		// <<<	- [!BASH] Passes the following word as standard input (⚠️ Le word subit certaines expansions, mais pas le word splitting ni le filename expansion, puis le résultat est fourni comme une seule string sur stdin, avec un `\n` ajouté)
	TOKEN_REDIR_ERR_OUT,	// &>	- [!BASH] Redirects both stdout and stderr (shorthand)
	TOKEN_APPEND_ERR_OUT,	// &>>	- [!BASH] Appends both stdout and stderr (shorthand)
	TOKEN_PIPE,				// |	- [POSIX] Passes standard output of one command to standard input of the next one
	TOKEN_PIPE_STDERR,		// |&	- [!BASH] Pipes both stdout and stderr to the next command
	// Category: TOKEN_CAT_CONTROL
	TOKEN_AND,				// &&	- [POSIX] Executes next command only if previous succeeded
	TOKEN_OR,				// ||	- [POSIX] Executes next command only if previous failed
	TOKEN_BACKGROUND,		// &	- [POSIX] Runs the command in a background process
	TOKEN_CASE_BREAK,		// ;;	- [POSIX] Ends a clause in a case conditional block
	TOKEN_SEQUENCE,			// ;	- [POSIX] Separates commands to run one after another
	TOKEN_NEWLINE,			// \n	- [POSIX] Acts as a command terminator, similar to ;
	TOKEN_SUBSHELL_START,	// (	- [POSIX] Opens a subshell environment
	TOKEN_SUBSHELL_END,		// )	- [POSIX] Closes a subshell environment
}	t_token_type;

typedef enum e_expand_type
{
	EXPAND_ALL,				// (can be a reserved word)
	EXPAND_VAR,				// (can NOT be a reserved word)
	EXPAND_NONE				// (can NOT be a reserved word)
}	t_expand_type;

typedef struct s_token
{
	t_token_category	category;		// [REQUIRED]
	t_token_type		type;			// [REQUIRED]
	char				*value;			// [REQUIRED] Array of characters
	t_expand_type		*expand_type;	// [NULL if category != TOKEN_CAT_WORD] Array of expand_type (one for each char in value)
}	t_token;

/**************************************************
L'objectif est que le lexer n'ait pas à connaitre toutes les expansions gérées par l'expander.
Ça simplifie son fonctionnement et ça améliore la maintenabilité / l'extensibilité :
Pour ajouter une expansion il suffit d'update l'expander, pas besoin d'update également le lexer
---------
QUOTE RULES (POSIX) :
- Simple quote				=> marquer chaque caractère comme EXPAND_NONE
- Hors quote				=> marquer chaque caractère comme EXPAND_ALL sauf :
	-> `\` + `\n`			=> supprimer les 2 caractères
	-> `\` + whatever		=> supprimer `\` et marquer le caractère suivant comme EXPAND_NONE
- Double quote				=> marquer chaque caractère comme EXPAND_VAR sauf :
	-> `\` + `\n`			=> supprimer les 2 caractères
	-> `\` + `$`			=> supprimer `\` et marquer le caractère suivant comme EXPAND_NONE
	-> `\` + ```			=> supprimer `\` et marquer le caractère suivant comme EXPAND_NONE
	-> `\` + `"`			=> supprimer `\` et marquer le caractère suivant comme EXPAND_NONE
	-> `\` + `\`			=> supprimer `\` et marquer le caractère suivant comme EXPAND_NONE
	-> `\` + whatever		=> conserver `\` et laisser le caractère suivant comme EXPAND_VAR
---------
N.B. :
- Le `\` est un "quoting" au sens POSIX
- Les quotes sont supprimées par le lexer et n'apparaissent donc pas dans les tokens
- Les extensions bash ajoutent `!` et les quoting ANSI-C ($'...') aux caractères spéciaux, mais on se limite ici à la norme POSIX
- Les reserved words (`if`, `then`, `fi`, `!`, `{`, `}`, etc sont détectés par le parser, ce sont de simples words pour le lexer)
---------
TEST CASES (VAR="world") :
echo 'hello $VAR \$42 *'	=> hello $VAR \$42 *
echo "hello $VAR \$42 *"	=> hello world $42 *
echo hello $VAR \$42 *		=> hello world $42 file1 file2 ...
echo \a						=> a
echo '\a'					=> \a
echo "\a"					=> \a
**************************************************/

t_list	lex(char *string);

#endif
