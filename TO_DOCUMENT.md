# TO DOCUMENT

## lr_machine.md

- Préciser que `ACTION` est complétée étape par étape avec un process et un payload différents pour :
	- `ERROR`: default
	- `SHIFT`: `action.payload` = `transition.to_lr_state_id`
	- `REDUCE`: `action.payload` = `lr_state[i].rule_state.rule_id` (only for `rules` with `pos` >= `rhs_len`)
	- `ACCEPT`: same as `REDUCE` but only if `rule.lhs` = `SYM_start` and for `SYM_EOF`

## What I learned

- Read, understand and implement an **industrial standard** (`POSIX`)
- Think, find and implement a suitable **architecture** for a large purpose program:
	- **deep modules** strategy: `scanner` (aka `lexer`) + `builder` (aka `parser`) + `runner` (aka `executor`)
	- **memory safety** flow: init, run, free
	- **error management**: handle various error types, printing and absorbing strategies
- Work as a **team** with `git` and `discord` (2 members):
	- **git branches**
	- **git issues**
	- **github actions** (`CI/CD`)
	- **discord hooks**
