# Table of contents

- [LR machine](#lr-machine)
- [Tokens](#tokens)
- [Symbols](#symbols)
- [Rules](#rules)
- [Rule States (RS)](#rule-states-rs)
- [LR State (LRS) and Transitions (T)](#lr-state-lrs-and-transitions-t)
- [Actions](#actions)
- [Gotos](#gotos)
- [Conflicts and lookahead](#conflicts-and-lookahead)

# LR machine

A `LR machine` translates a given `grammar` into `action` and `goto` tables.  
These tables are created only once (at ***compile-time*** or ***startup-time***).  
Then the `parser` will use them at ***runtime*** to build the `AST` by performing the following actions:
- ***peek***: look at the next `token(s)` it **could** ***shift***
- ***shift***: consume a `token` and convert it to a ***terminal*** `symbol`
- ***reduce***: merge `symbols` together
- eventually ***accept*** or ***reject*** the `input`

> 💡 The following examples use a very simple grammar for pedagogical purpose.  
> Examples show a `LR(0)` implementation, which can **NOT** resolve ***shift-reduce*** / ***reduce-reduce*** conflicts.  
> The specificity of `LR(1)` parsers (`lookahead`) will be discussed in the last section to explain how these conflicts can be resolved.

# Tokens

A `token` is the minimal ***lexical*** unit that can be recognized in the `input` **without any *syntactic context***.  

The `scanner` (aka `lexer`) splits the `input` into `tokens` and exposes an API to let the `parser` ***shift*** and/or ***peek*** them when needed.

# Symbols

The `parser` creates `symbols` by converting `tokens` into ***terminal*** `symbols` before ***reducing*** them into ***non-terminal*** ones.

- ***Terminals*** (raw symbols):
	- `WORD`
- ***Non-terminals*** (reduced symbols, built following the grammar `rules`):
	- `cmd`, `name`, `arg`
- ***Start symbol*** (special ***non-terminal*** symbol which means parser can now ***accept*** the input as a valid one):
	- `start`
- ***EOF symbol*** (special ***terminal*** symbol which means parser has reached the end of the `input`):
	- `EOF`

# Rules

Grammar `rules` that describe how `symbols` can be combined together.

| Rule | LHS         | RHS             |
| ---- | ----------- | --------------- |
| 1    | `start`     | -> `cmd`        |
| 2    | `cmd`       | -> `name` `arg` |
| 3    | `cmd`       | -> `name`       |
| 4    | `name`      | -> `WORD`       |
| 5    | `arg`       | -> `WORD`       |

## Rule States (RS)

A `rule state` (aka `item`) represents the state of a given grammar `rule` at a given point in the parse.

| RS | Rule | LHS     | RHS               |
| -- | ---- | ------- | ----------------- |
| 1  | 1    | `start` | -> • `cmd`        |
| 2  | 1    | `start` | -> `cmd` •        |
| 3  | 2    | `cmd`   | -> • `name` `arg` |
| 4  | 2    | `cmd`   | -> `name` • `arg` |
| 5  | 2    | `cmd`   | -> `name` `arg` • |
| 6  | 3    | `cmd`   | -> • `name`       |
| 7  | 3    | `cmd`   | -> `name` •       |
| 8  | 4    | `name`  | -> • `WORD`       |
| 9  | 4    | `name`  | -> `WORD` •       |
| 10 | 5    | `arg`   | -> • `WORD`       |
| 11 | 5    | `arg`   | -> `WORD` •       |

## LR State (LRS) and Transitions (T)

A `LR state` (aka `state`) is a set of `rule states` (aka `items`) that are **simultaneously valid** at a given point in the parse.

`LR state` and `transition` tables are built starting from the `start` `rule` with the `dot` at position 0.  
Following `LR states` are built while exploring all the possible `transitions` from this initial `LR state`:
- Start by creating `LRS1`
- List all transitions from `LRS1`
- Each transition may discover a new `LR state`
- Repeat the process from each newly discovered `LR state`
- Never duplicate an existing `LR state`

> ⚠️ A `rule state` is included in the `LR state` table only if it is discovered while exploring the `transitions` from `LRS1`.  
> In this small grammar, all `rule states` happen to be discovered.

> ⚠️ Only the next `symbol` to parse is considered.  
Following `symbols` are handled in other `LR states` (aka `states`) because they are not yet valid.  
=> *e.g. for `LRS1`: `arg` is not valid before `name` has been recognized, even if it is part of `RS3` which is included in `LRS1`*

| T | From   | With   | LRS | RS           | Expected ***terminal***                                                                                   | 💥 Conflict        |
| - | ------ | ------ | --- | ------------ | --------------------------------------------------------------------------------------------------------- | ------------------ |
|   |        |        | 1   | [1, 3, 6, 8] | Expecting [`cmd` (cf `RS1`) => `name` (cf `RS3`/`RS6`) => `WORD` (cf `RS8`)]                              |                    |
| 1 | `LRS1` | `cmd`  | 2   | [2]          | Expecting [`EOF` => ***accept*** available]                                                               |                    |
| 2 | `LRS1` | `name` | 3   | [4, 7, 10]   | Expecting [`arg` (cf `RS4`) => `WORD` (cf `RS10`)] or [*nothing* (cf `RS7`) => ***reduction*** available] | ***shift-reduce*** |
| 3 | `LRS1` | `WORD` | 4   | [9]          | Expecting [*nothing* (cf `RS9`) => ***reduction*** available]                                             |                    |
| 4 | `LRS3` | `arg`  | 5   | [5]          | Expecting [*nothing* (cf `RS5`) => ***reduction*** available]                                             |                    |
| 5 | `LRS3` | `WORD` | 6   | [11]         | Expecting [*nothing* (cf `RS11`) => ***reduction*** available]                                            |                    |

## Actions

The `action` table tells the `parser` what to do when the next symbol to parse is a ***terminal***:
- ***shift*** a new ***terminal symbol*** and move to another `LR state`
- ***reduce*** using a grammar `rule`
- ***accept*** the `input`
- or ***reject*** the `input` if no `action` is available

> ⚠️ `action` is used only with ***terminal*** symbols.  
> ***Non-terminal*** symbols always use the `goto` table.

> ⚠️ In a `LR(0)` machine, a complete `rule state` (`•` at the end) makes the parser want to ***reduce*** **without looking ahead**.  
> This is why conflicts may appear: the parser may want to ***shift*** and ***reduce*** at the same time.

> 💡 In this simplified example, once `LRS2` is reached, the `start` symbol is complete (`start -> cmd •`).  
> If the next terminal is `EOF`, the `input` can now be ***accepted***.

| LRS | `WORD`                                                | `EOF`                    |
| --- | ----------------------------------------------------- | ------------------------ |
| 1   | ***shift*** -> `LRS4`                                 | ***reject***             |
| 2   | ***reject***                                          | ***accept***             |
| 3   | ***shift*** -> `LRS6` **OR** ***reduce*** by `rule 3` | ***reduce*** by `rule 3` |
| 4   | ***reduce*** by `rule 4`                              | ***reduce*** by `rule 4` |
| 5   | ***reduce*** by `rule 2`                              | ***reduce*** by `rule 2` |
| 6   | ***reduce*** by `rule 5`                              | ***reduce*** by `rule 5` |

> ⚠️ `LRS3` contains a ***shift-reduce conflict*** on `WORD`:
> - `cmd -> name •` wants to ***reduce*** using `rule 3`
> - `arg -> • WORD` wants to ***shift*** `WORD`

## Gotos

The `goto` table tells the `parser` which `LR state` must be reached after a ***reduction*** created a ***non-terminal*** symbol.

> ⚠️ `goto` is used only with ***non-terminal*** symbols.  
> ***Terminal*** symbols always use the `action` table.

| LRS | `cmd`  | `name` | `arg`  |
| --- | ------ | ------ | ------ |
| 1   | `LRS2` | `LRS3` |        |
| 2   |        |        |        |
| 3   |        |        | `LRS5` |
| 4   |        |        |        |
| 5   |        |        |        |
| 6   |        |        |        |

> 💡 Example:
> - in `LRS4`, `rule 4` (`name -> WORD`) can be reduced (cf `action` table)
> - this creates the non-terminal symbol `name`
> - from the state below on the stack (`LRS1`), `goto[LRS1][name] = LRS3`
> - so the parser continues in `LRS3`

## Conflicts and lookahead

A ***conflict*** happens when the `parser` can **NOT** choose a single `action` from the current `LR state`:
- ***shift-reduce conflict***:
	- the `parser` can either ***shift*** the next ***terminal*** `symbol` **OR** ***reduce*** using a complete `rule`
	- a `LR(0)` `parser` can **NOT** resolve this conflict because complete `rule states` always suggest ***reduction***, independently of the next ***terminal*** `symbol`.
- ***reduce-reduce conflict***:
	- the `parser` can ***reduce*** using more than one complete `rule`
	- a `LR(0)` `parser` can **NOT** resolve this conflict because it does **NOT** look at the next ***terminal*** `symbol` before deciding which complete `rule` may ***reduce***.

In this example, only one conflict exists:
- in `LRS3` on `WORD`:
	- `cmd -> name •` suggests ***reduce*** by `rule 3`
	- `arg -> • WORD` suggests ***shift*** to continue `rule 2`

> 💡 A `LR(1)` `parser` adds a ***lookahead*** to each `item`, which means:
> - the `parser` still tracks the current `LR state`
> - but each possible ***reduction*** is now limited to specific next ***terminal*** `symbols`

> 👉 In this grammar, one-token `lookahead` is enough to resolve the conflict in `LRS3`:
> - if the next ***terminal*** is `WORD`, the `parser` should ***shift*** to parse `arg`
> - if the next ***terminal*** is `EOF`, the `parser` should ***reduce*** by `rule 3` (`cmd -> name`)

| LRS | Lookahead | Correct `action`         |
| --- | --------- | ------------------------ |
| 3   | `WORD`    | ***shift*** -> `LRS6`    |
| 3   | `EOF`     | ***reduce*** by `rule 3` |

> 👉 This grammar is **NOT** `LR(0)` but **is** `LR(1)`:
> one `token` of `lookahead` is enough to choose the correct `action`.
