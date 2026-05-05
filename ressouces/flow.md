# High level flow

🎬 [Compiler full course](https://youtube.com/playlist?list=PLiU6EYjTWtuXQ0T2oh7vztsujfubPnk90&si=_OdzPvRRDgDeSH7f)  
📚 [2.1 Shell Introduction](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_01)

## Table of contents

- [Overview](#overview)
- [Lexer](#scanner)
	- [Reader](#reader)
	- [Tokenizer](#tokenizer)
- [Parser](#parser)
- [Executor](#executor)

## Overview

| # | Input              | Stage        | Output                                    |
| - | ------------------ | ------------ | ----------------------------------------- |
| 1 | `char *`           | **SCANNER**    | `tokens`                                  |
| 2 | `tokens`           | **PARSER**   | `CST`                                     |
| 3 | `CST`              | **BUILDER**  | `AST`                                     |
| 4 | `AST`              | **WALKER**   | `command node`                            |
| 5 | `command node`     | **EXPANDER** | `expanded command`                        |
| 6 | `expanded command` | **RUNNER**   | `redirections + builtin/fork/exec + wait` |

## Lexer

📚 [2.2 Quoting](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_02)  
📚 [2.3 Token Recognition](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_03)  
📚 [2.7 Redirection](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_07)  
📚 [2.10 Shell Grammar](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_10)  

### Reader

> *"The shell reads its input from a file"*

1. **Input Reading**
	- Input: none (`void`)
	- Output: line (`char *`)
	- Note: *"The shell shall read its input in terms of lines"* ([sh](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html#))
	- Note: *"Line joining is done before tokenization"* ([2.2.1 Escape Character (Backslash)](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_02_01))

### Tokenizer

> *"The shell breaks the input into tokens: words and operators"*

2. **Token Recognition**
	- Input:  line (`char *`)
	- Output: token (`char *`)
	- [2.3 Token recognition](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_03) (Default mode)
		- Special characters to identify: comments -> `#`
		- Special characters to identify: quotes -> `'`, `"`, `\`
		- Special characters to identify: expansion / substitution -> ```, `$`, `${`, `$(`, `$((`
		- ⚠️ Note: *"For `$(` and '\`' only, if instances of `io_here` tokens are found nested within the substitution, they shall be parsed according to the rules of [2.7.4 Here-Document](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_07_04); if the terminating ')' or '\`' of the substitution occurs before the `NEWLINE` token marking the start of the `here-document`, the behavior is unspecified"*
		- Note: *The shell shall identify quoting and the start of any candidates for parameter expansion, command substitution or arithmetic expansion*
		- Note: *"No substitutions shall be actually performed, and the result token shall contain exactly the characters that appear in the input unmodified"*
		- Note: *"The token shall not be delimited by the end of the quoted field or by the end of the substitution"*
	- [2.7.4 Here-Document](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_07_04) (here-document mode)
		- Mode is switched after the next `NEWLINE` after a detected `io_here`
		- Note: *"Any non-NEWLINE tokens (including more io_here tokens) that are recognized while searching for the next NEWLINE token shall be saved for processing after the here-document has been parsed"*
		- ⚠️ **TODO**

3. **Immediate Context Classification**
	- Input: token (`char *`)
	- Output: token identifier (`t_token_id`: operator identifier, `IO_NUMBER`, `TOKEN`)
	- [2.10.1 Shell Grammar Lexical Conventions](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_10_01)
	- [XBD 3.85 Control Operators](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/V1_chap03.html#tag_03_85)
	- [XBD 3.304 Redirection Operators](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/V1_chap03.html#tag_03_304)

4. **Alias Substitution**
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

## Parser

🎬 [Bottom-up parser `LR(1)`](https://www.youtube.com/watch?v=-262vfWJfAg)  
📚 [2.4 Reserved Words](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_04)  
📚 [2.9 Shell Commands](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_09)  
📚 [2.10 Shell Grammar](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_10)  

> *"The shell parses the input into simple commands and compound commands"*

5. **Context-dependent Classification**
	- Input 1: context (⚠️ **TODO**)
	- Input 2: token (`char *`) only if
		- The token has been classified as `TOKEN` at step 3
	- Output: token identifier (`t_token_id`: reserved word identifier, `WORD`, `NAME`, `ASSIGNMENT_WORD`)
	- [2.10.2 Shell Grammar Rules](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_10_02)
		- Note: *"Some of the productions in the grammar below are annotated with a rule number"*
		- Note: *"The expansions specified in [2.7 Redirection](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_07) shall occur"*
		- Note: *"Quote removal shall be applied to the word to determine the delimiter that is used to find the end of the here-document"*
	- [2.4 Reserved Words](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_04)
		- ⚠️ **TODO**

6. **AST building**
	- 📖 `terminal token`: lowest token level (generated by **scanner**)
	- 📖 `token`: high level token (generated by **parser** by merging `terminal tokens` and/or `tokens`)
	- 📖 `rule`: allowed ways to merge `tokens`
		- 📖 `LHS`: `L`eft `H`and`S`ide of the `rule`
		- 📖 `RHS`: `R`ight `H`and`S`ide of the `rule`
	- 📖 `ambigous grammar`: when the grammar `rules` allow more than one `AST` for the same input
	- 📖 `start symbol`: token which must be reached at the top of the `AST`
	- 📖 `bottom-up`:
		- aka `LR(1)`:
			- Tokens read from `L`eft
			- `R`ight-most traversal reverse
			- `1` token at a time
		- 📖 `shift`: add a `token` to the `stack`, the `token` is considered `consumed`
		- 📖 `peek`: look to a `token` ahead in the stream (**NOT** `consumed`)
		- 📖 `reduce`: create a `subtree` by merging `tokens` into a higher-level `token` when a `grammatical rule` can be applied
			- 💡 Reduce only whenonly **ONE** `rule` is valid with current `tokens` (or current `tokens` + `peek(x)`)
		- 📖 `shift-reduce conflict`: when **parser** can **NOT** know if it should `shift` a new `token` or `reduce` the existing ones
		- 📖 `reduce-reduce conflict`: when **parser** can **NOT** know which `rule` it should use to `reduce` the `tokens` on the stack
	- 📖 `Command` -> `pipeline` -> `and_or` -> `list` -> `program`
	- Loop through `tokens`:
		- `shift()`
		- `reduce()`
		- If `start symbol` is reached: **execute**
		- Else if `EOF` is reached: **error**

## Executor

📚 [2.2 Quoting](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_02)  
📚 [2.5 Parameters and Variables](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_05)  
📚 [2.6 Word Expansions](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_06)  
📚 [2.7 Redirection](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_07)  
📚 [2.8 Exit Status and Errors](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_08)  
📚 [2.9 Shell Commands](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_09)  

> *"For each word within a command, the shell processes expansions"*

7. **Word expansion**
	- 📚 [2.6 Word Expansions](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_06)
	1. Prioritary expansions: 
		- [Tilde Expansion](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_06_01)
		- [Parameter Expansion](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_06_02)
		- [Command Substitution](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_06_03)
		- [Arithmetic Expansion](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_06_04)
		- ⚠️ Note: *"beginning to end"*
		- Note: *"See item 5 in [2.3 Token Recognition](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_03)"*
	2. [Field Splitting](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_06_05)
	3. [Pathname Expansion](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_06_06)
		- Note: unless `set -f` is in effect.
	4. [Quote Removal](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_06_07)
		- ⚠️ Note: *"if performed"*

> *"The shell performs redirection and removes redirection operators and their operands from the parameter list"*

8. **Redirection**
	- 📚 [2.7 Redirection](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_07)
	- ⚠️ **TODO**

> *"The shell executes a [function](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_09_05), [built-in](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_15), executable file, or script."*

9. **Execution**
	- 📚 [2.9 Shell Commands](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_09)
	- ⚠️ **TODO**

> *"The shell optionally waits for the command to complete and collects the [exit status](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_08_02)"*

10. **Wait and Collect**
	- 📚 [2.8 Exit Status and Errors](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_08_02)
	- ⚠️ **TODO**
