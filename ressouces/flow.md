FLOW
1. **[LEXER] Reading**
	- Output: line (`char *`)
	- [sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html#) (line by line reading)
		- Note: *"The shell shall read its input in terms of lines"*
		- Note: *"Line joining is done before tokenization"* cf [2.2.1 Escape Character (Backslash)](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_02_01)
2. **[LEXER] Token Recognition**
	- Input:  line (`char *`)
	- Output: token (`char *`)
	- [2.3 Token recognition](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_03) (Default mode)
		- Special characters to identify: comments -> `#`
		- Special characters to identify: quotes -> `'`, `"`, `\`
		- Special characters to identify: expansion / substitution -> ```, `$`, `${`, `$(`, `$((`
		- ⚠️ Note: *"For "$(" and '`' only, if instances of io_here tokens are found nested within the substitution, they shall be parsed according to the rules of 2.7.4 Here-Document; if the terminating ')' or '`' of the substitution occurs before the NEWLINE token marking the start of the here-document, the behavior is unspecified"*
		- Note: *The shell shall identify quoting and the start of any candidates for parameter expansion, command substitution or arithmetic expansion*
		- Note: *"No substitutions shall be actually performed, and the result token shall contain exactly the characters that appear in the input unmodified"*
		- Note: *"The token shall not be delimited by the end of the quoted field or by the end of the substitution"*
	- [2.7.4 Here-Document](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_07_04) (here-document mode)
		- Mode is switched after the next `NEWLINE` after a detected `io_here`
		- Note: *"Any non-NEWLINE tokens (including more io_here tokens) that are recognized while searching for the next NEWLINE token shall be saved for processing after the here-document has been parsed"*
		- **TODO**
3. **[LEXER] Immediate Context Classification**
	- Input: token (`char *`)
	- Output: token identifier (`t_token_id`: operator identifier, `IO_NUMBER`, `TOKEN`)
	- ⚠️ special separators: `NEWLINE`, `;`, `&`, `|`
	- [2.10.1 Shell Grammar Lexical Conventions](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_10_01)
	- [XBD 3.85 Control Operators](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/V1_chap03.html#tag_03_85)
	- [XBD 3.304 Redirection Operators](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/V1_chap03.html#tag_03_304)
4. **[LEXER] Alias Substitution**
	- Input: token (`char *`) only if
		- The token has been classified as `TOKEN` at step 3
		- The token does not contain any quoting characters
		- The token is a valid alias name cf [XBD 3.10 Alias Name](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/V1_chap03.html#tag_03_10)
		- An alias with that name is in effect
		- The token did not either fully or, optionally, partially result from an alias substitution of the same alias name at any earlier recursion level
		- ⚠️ Either the token is being considered for alias substitution because it follows an alias substitution whose replacement value ended with a \<blank> (see below) or the token could be parsed as the command name word of a simple command cf [2.10 Shell Grammar](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_10), based on this token and the tokens (if any) that preceded it, but ignoring whether any subsequent characters would allow that
		- Note: *"When a TOKEN is subject to alias substitution, the value of the alias shall be processed as if it had been read from the input"*
	- Output: token (`char *`)
	- [2.3.1 Alias Substitution](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_03_01)
5. **[PARSER] Context-dependent Classification**
	- Input 1: context (**TODO**)
	- Input 2: token (`char *`) only if
		- The token has been classified as `TOKEN` at step 3
	- Output: token identifier (`t_token_id`: reserved word identifier, `WORD`, `NAME`, `ASSIGNMENT_WORD`)
	- [2.10.2 Shell Grammar Rules](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_10_02)
		- Note: *"Some of the productions in the grammar below are annotated with a rule number"*
		- Note: *"The expansions specified in [2.7 Redirection](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_07) shall occur"*
		- Note: *"Quote removal shall be applied to the word to determine the delimiter that is used to find the end of the here-document"*
	- [2.4 Reserved Words](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_04)
6. **[PARSER] AST builder**
	- **TODO**
