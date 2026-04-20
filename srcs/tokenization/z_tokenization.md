# Token types

```c
/*
EXP_NONE
EXP_VAR			- Variable expansion: $VAR or ${VAR}
EXP_TILDE		- Tilde expansion: ~/path
EXP_WILDCARD	- Pathname expansion: *.c, ?, [a-z]
EXP_CMD_SUB		- Command substitution: $(ls) or `ls`
EXP_ARITHMETIC	- Arithmetic: $((1 + 1))
EXP_BRACE		- Brace expansion: {a,b}c -> ac bc
EXP_PARAM		- Parameter expansion: ${VAR:-default}, ${VAR%suffix} etc
EXP_QUOTED		- Indicates the word was inside "" or ''
EXP_DQUOTED		- Specifically inside double quotes
*/
typedef enum e_expand_type
{
    EXP_NONE            = 0,
    EXP_VAR             = 1 << 0,
    EXP_TILDE           = 1 << 1,
    EXP_WILDCARD        = 1 << 2, 
    EXP_CMD_SUB         = 1 << 3, 
    EXP_ARITHMETIC      = 1 << 4, 
    EXP_BRACE           = 1 << 5, 
    EXP_PARAM           = 1 << 6, 
    EXP_QUOTED          = 1 << 7, 
    EXP_DQUOTED         = 1 << 8  
}   t_expand_type;

/*
Tells the parser how to treat it in the grammar
TOKEN_CAT_LITERAL 		- The "meat" of the command (program names, arguments,
							or raw numbers for file descriptors)
TOKEN_CAT_REDIRECTION 	- Tell the shell to move data between files and file
							descriptors
TOKEN_CAT_OPERATOR 		- Manipulate the "plumbing" of the command pipeline
TOKEN_CAT_CONTROL 		- Define the flow of execution—deciding if or when a
							command runs
TOKEN_CAT_GROUPING		- Create "blocks" of logic
TOKEN_CAT_END			- Marks the end of the input or a file
TOKEN_CAT_ERROR			- Signal that it encountered a character it doesn't
							recognize or a syntax error
*/
typedef enum e_token_category
{
	TOKEN_CAT_LITERAL,
	TOKEN_CAT_REDIRECTION,
	TOKEN_CAT_OPERATOR,
	TOKEN_CAT_CONTROL,
	TOKEN_CAT_GROUPING,
	TOKEN_CAT_END,
	TOKEN_CAT_ERROR
}	t_token_category;

/*
Tells exactly to the parser what the character is
// Category: Literal
TOKEN_WORD					- Standard words (ls, -la, filename)
TOKEN_IO_NUMBER				- Digit(s) prefixing a redirection (the 2 in 2>)
// Category: Redirection
TOKEN_REDIR_IN			<	- RedirectS file to standard input
TOKEN_REDIR_OUT			>	- RedirectS standard output to a file (truncate)
TOKEN_APPEND			>>	- RedirectS standard output to a file (append)
TOKEN_HEREDOC			<<	- Reads input until a delimiter string is reached
TOKEN_REDIR_IN_OUT		<>	- Opens a file for both reading and writing
TOKEN_DUP_IN			<&	- Duplicates an input file descriptor
TOKEN_DUP_OUT			>&	- Duplicates an output file descriptor
TOKEN_CLOBBER			>|	- Overwrites a file even if noclobber is on
TOKEN_HERE_STRING		<<<	- Passes the following word as standard input
TOKEN_HEREDOC_STRIP		<<-	- Heredoc that strips leading tabs from the input
TOKEN_REDIR_ERR_OUT		&>	- Redirects both stdout and stderr (shorthand)
TOKEN_APPEND_ERR_OUT	&>>	- Appends both stdout and stderr (shorthand)
// Category: Operator
TOKEN_PIPE				|	- Passes output of one command to input of next
TOKEN_PIPE_STDERR		|&	- Pipes both stdout and stderr to the next command
TOKEN_NEGATION			!	- Inverts the logical exit status of the command
// Category: Control
TOKEN_AND				&&	- Executes next command only if previous succeeded
TOKEN_OR				||	- Executes next command only if previous failed
TOKEN_BACKGROUND		&	- Runs the command in a background process
TOKEN_SEQUENCE			;	- Separates commands to run one after another
TOKEN_CASE_BREAK		;;	- Ends a clause in a case conditional block
TOKEN_NEWLINE			\n	- Acts as a command terminator, similar to ;
// Category: Grouping
TOKEN_SUBSHELL_START	(	- Opens a subshell environment
TOKEN_SUBSHELL_END		)	- Closes a subshell environment
TOKEN_BLOCK_START		{	- Starts a command group in the current shell
TOKEN_BLOCK_END			}	- Ends a command group in the current shell
// Special
TOKEN_EOF					- Marks the end of the input or a file
TOKEN_ERROR					- Signal that it encountered a character it doesn't
								recognize or a syntax error
*/
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_IO_NUMBER,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_REDIR_IN_OUT,
	TOKEN_DUP_IN,
	TOKEN_DUP_OUT,
	TOKEN_CLOBBER,
	TOKEN_HERE_STRING,
	TOKEN_HEREDOC_STRIP,
	TOKEN_REDIR_ERR_OUT,
	TOKEN_APPEND_ERR_OUT,
	TOKEN_PIPE,
	TOKEN_PIPE_STDERR,
	TOKEN_NEGATION,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_BACKGROUND,
	TOKEN_SEQUENCE,
	TOKEN_CASE_BREAK,
	TOKEN_NEWLINE,
	TOKEN_SUBSHELL_START,
	TOKEN_SUBSHELL_END,
	TOKEN_BLOCK_START,
	TOKEN_BLOCK_END,
	TOKEN_EOF,
	TOKEN_ERROR
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	t_token_category	category;
	t_expand_type		expand_type;
}	t_token

typedef token*	tokens;
```

tokens = token[]
token
{
	is_literal : bool
	value	   : string
}

quote : quote_status = NONE | WEAK | STRONG
tokenizer_state
{
	is_ended : bool
	index	 : int
	value	 : tokens 
	quote	 : quote_status
}

## Escapables
general_escapables : 
in_quote_escapables : string[] = ['$', '"', '\', '`', '\n']

## Separators
blank_separators : string[] = [' ', '\t']
command_separators : string[] = [";", "&&", "||", "|"]
operators_separators : string[][] =
[
	["&>>", "<<<", "<<-"],
	[";;", "||", "|&", "&&", "&>", ">>", ">|", ">&", "<<", "<>", "<&"]
	["\n","(",")",";", "|", "&",">", "<"]
]

//------------ Tokenizer Utils ------------

fun literal_token(value : string) : token
	return ({value : value, is_literal : true})

fun special_token(value : string) : token
	return ({value : value, is_literal : false})

fun	is_blank_separator(value : char) : bool
	return (value in blank_separator)

fun	is_quote_escapable(value : char) : bool
	return (value in in_quote_escapables)

fun add_token(&state : tokenizer_state, token : token) : void
	if (state->value.len == 0 || state->value[state->value.len].len == 0)
		state->value[state->value.len] = token
	else
		if (state->is_ended == true)
			state->value += token
			state->is_ended = false
		else if (token.is_literal == false)
			state->value += token
			state->is_ended = true
		else
			if (state->value[last].is_literal == true)
            	state->value[last].value += token.value
        	else
            	state->value += token

//------------ Tokenization ------------

//	------ Escape ------
fun	tokenize_escaped(
	input  : string,
	&index : int,
	&state : tokenizer_state,
) : void
	if (input[*index + 1] != '\n')
		add_token(state, literal_token(input[++(*index)++].toString))
	else
		(*index) += 2

fun	tokenize_quoted_escaped(
	input  : string,
	&index : int,
	&state : tokenizer_state,
) : void
	if (is_quote_escapable(input[*index + 1]))
		tokenize_escaped(input, index, state)
	else
		add_token(state, literal_token(input[*index++].toString))
		add_token(state, literal_token(input[*index++].toString))

//	------ Separator ------
fun	end_token_with_blank(
	input  : string,
	&index : int,
	&state : tokenizer_state,
) : bool
	if (is_blank_separator(input[*index]))
		state->is_ended = true
	loop input start *index_space while (is_blank_separator(input[*index]))
		++(*index)
	return (state->is_ended)

fun	end_token_with_operator(
	input  : string,
	&index : int,
	&state : tokenizer_state,
) : bool
	operator_str = ""
	loop operators[0] with index_operator while (operator_str.len == 0)
		if (str_ncmp(input + (*index), operators[0][index_operator], 3))
			operator_str = input[*index] + input[*index + 1] + input[*index + 2]
	loop operators[1] with index_operator while (operator_str.len == 0)
		if (str_ncmp(input + (*index), operators[1][index_operator], 2))
			operator_str = input[*index] + input[*index + 1]
	loop operators[2] with index_operator while (operator_str.len == 0)
		if (str_ncmp(input + (*index), operators[2][index_operator], 1))
			operator_str = input[*index]
	if (operator_str.len != 0)
		state->is_ended = true
		add_token(state, special_token(operator_str))
		*index += operator_str.len
	return (state->is_ended)

//	------ Tokenizer ------
fun	tokenize_standard(
	input  : string,
	&index : int,
	&state : tokenizer_state,
) : void
	if (state->quote == STRONG)
		add_token(state, literal_token(input[(*index)++].toString))
	else if (state->quote == WEAK)
		if (input[*index] == '$' || input[*index] == '`')
			state->is_ended = true
			add_token(state, special_token(input[(*index)++].toString))
		else if (input[*index] == '\')
			tokenize_quoted_escaped(input, index, state)
		else
			add_token(state, literal_token(input[(*index)++].toString))
	else
		if (!end_token_with_blank(input, index, state))
			if (!end_token_with_operator(input, index, state))
				add_token(state, literal_token(input[(*index)++].toString))

fun	tokenize(input : string) : tokens
	state : tokenizer_state =
	{
		index	 : 0,
		value	 : [],
		is_ended : false,
		quote	 : NONE,
	}
	loop input with index
		if (input[index] == '\')
			tokenize_escaped(input, &index, &state)
		else if (input[index] == ''' && state.quote != WEAK)
			state.quote = (state.quote == STRONG) ? NONE : STRONG
			++index
		else if (input[index] == '"' && state.quote != STRONG)
			state.quote = (state.quote == WEAK) ? NONE : WEAK
			++index
		else
			tokenize_standard(input, &index, &state)
	return (state->value)
