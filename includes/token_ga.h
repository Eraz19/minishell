#ifndef TOKEN_GA_H
# define TOKEN_GA_H

# include <stddef.h>

typedef enum e_token_category
{
	TOKEN_CAT_WORD,			// Program name, arguments, raw numbers for file descriptors...
	TOKEN_CAT_REDIRECTION,	// Data source / target (files / file descriptors)
	TOKEN_CAT_OPERATOR,		// Pipes and exit status inversions
	TOKEN_CAT_CONTROL,		// If or when a command runs
	TOKEN_CAT_GROUPING,		// Blocks of logic
	TOKEN_CAT_END,			// End of input / file (TODO: useless ?? => no use case ??)
	TOKEN_CAT_ERROR			// Unrecognized character / syntax (TODO: useless ?? => immediatly throw error instead ?)
}	t_token_category;

typedef enum e_token_type
{
	// Category: TOKEN_CAT_WORD
	TOKEN_WORD,				//
	TOKEN_IO_NUMBER,		//
	// Category: TOKEN_CAT_REDIRECTION
	TOKEN_REDIR_IN,			//
	TOKEN_REDIR_OUT,		//
	TOKEN_APPEND,			//
	TOKEN_HEREDOC,			//
	TOKEN_REDIR_IN_OUT,		//
	TOKEN_DUP_IN,			//
	TOKEN_DUP_OUT,			//
	TOKEN_CLOBBER,			//
	TOKEN_HERE_STRING,		//
	TOKEN_HEREDOC_STRIP,	//
	TOKEN_REDIR_ERR_OUT,	//
	TOKEN_APPEND_ERR_OUT,	//
	// Category: TOKEN_CAT_OPERATOR
	TOKEN_PIPE,				//
	TOKEN_PIPE_STDERR,		//
	TOKEN_NEGATION,			//
	// Category: TOKEN_CAT_CONTROL
	TOKEN_AND,				//
	TOKEN_OR,				//
	TOKEN_BACKGROUND,		//
	TOKEN_SEQUENCE,			//
	TOKEN_CASE_BREAK,		//
	TOKEN_NEWLINE,			//
	// Category: TOKEN_CAT_GROUPING
	TOKEN_SUBSHELL_START,	//
	TOKEN_SUBSHELL_END,		//
	TOKEN_BLOCK_START,		//
	TOKEN_BLOCK_END,		//
	// Category: TOKEN_CAT_END
	TOKEN_EOF,				//
	// Category: TOKEN_CAT_ERROR
	TOKEN_ERROR				//
}	t_token_type;

typedef enum e_expand_type
{
	EXP_ALL,				// No quote
	EXP_VAR,				// Double quotes
	EXP_NONE				// Single quotes
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
ESCAPE RULES (POSIX) :
- Simple quote				=> marquer chaque caractère comme EXPAND_NONE
- Hors quote				=> marquer chaque caractère comme EXPAND_ALL sauf :
	-> `\` + `newline`		=> supprimer les 2 caractères
	-> `\` + whatever		=> supprimer `\` et marquer le caractère suivant comme EXPAND_NONE
- Double quote				=> marquer chaque caractère comme EXPAND_VAR sauf :
	-> `\` + `newline`		=> supprimer les 2 caractères
	-> `\` + `$`			=> supprimer `\` et marquer le caractère suivant comme EXPAND_NONE
	-> `\` + ```			=> supprimer `\` et marquer le caractère suivant comme EXPAND_NONE
	-> `\` + `"`			=> supprimer `\` et marquer le caractère suivant comme EXPAND_NONE
	-> `\` + `\`			=> supprimer `\` et marquer le caractère suivant comme EXPAND_NONE
	-> `\` + whatever		=> conserver `\` et laisser le caractère suivant comme EXPAND_VAR
---------
N.B. :
- Les quotes sont supprimées par le lexer et n'apparaissent donc pas dans les tokens
- Les extensions bash ajoutent `!` et les quoting ANSI-C ($'...') aux caractères spéciaux, mais on se limite ici à la norme POSIX
---------
TEST CASES (VAR="world") :
echo 'hello $VAR \$42 *'	=> hello $VAR \$42 *
echo "hello $VAR \$42 *"	=> hello world $42 *
echo hello $VAR \$42 *		=> hello world $42 file1 file2 ...
echo \a						=> a
echo '\a'					=> a
echo "\a"					=> \a
**************************************************/

#endif
