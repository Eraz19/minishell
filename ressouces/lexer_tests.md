# Shell Lexer Test Suite

A reference test suite for a shell lexer that preserves quoting and escape
characters inside word tokens (quote removal is deferred to expansion time).

## Conventions

- `WORD("x")` — word token whose raw payload bytes are the C string `"x"`.
- `IO_NUMBER("x")` — digit-string token immediately preceding `<` or `>`.
- `NL` — newline token.
- `EOF` — end of input.
- Operator tokens: `PIPE` (`|`), `OR_IF` (`||`), `AMP` (`&`), `AND_IF` (`&&`),
  `SEMI` (`;`), `DSEMI` (`;;`), `LESS` (`<`), `GREAT` (`>`), `DLESS` (`<<`),
  `DGREAT` (`>>`), `LESSAND` (`<&`), `GREATAND` (`>&`), `LESSGREAT` (`<>`),
  `CLOBBER` (`>|`), `DLESS_DASH` (`<<-`), `LPAREN` (`(`), `RPAREN` (`)`).
- In the "Shell input" column, `↵` represents a literal `0x0A` newline byte.
- The "C input" column is the C string literal you pass to `lex_init()` or
  equivalent in your test harness. The payload strings inside `WORD(...)` and
  `IO_NUMBER(...)` are also C string literals — you can `memcmp` the token
  payload against them directly.

---

## 1. Trivial inputs

| #   | Shell input | C input   | Expected tokens |
|-----|-------------|-----------|-----------------|
| 1.1 | (empty)     | `""`      | `EOF` |
| 1.2 | `   `       | `"   "`   | `EOF` |
| 1.3 | `\t\t`      | `"\t\t"`  | `EOF` |
| 1.4 | `↵`         | `"\n"`    | `NL, EOF` |
| 1.5 | `↵↵↵`       | `"\n\n\n"`| `NL, NL, NL, EOF` |
| 1.6 | `   ↵   `   | `"   \n   "` | `NL, EOF` |

---

## 2. Simple words

| #   | Shell input               | C input                       | Expected tokens |
|-----|---------------------------|-------------------------------|-----------------|
| 2.1 | `echo hello`              | `"echo hello"`                | `WORD("echo"), WORD("hello"), EOF` |
| 2.2 | `   echo   hello   `      | `"   echo   hello   "`        | `WORD("echo"), WORD("hello"), EOF` |
| 2.3 | `\techo\thello`           | `"\techo\thello"`             | `WORD("echo"), WORD("hello"), EOF` |
| 2.4 | `abc`                     | `"abc"`                       | `WORD("abc"), EOF` |
| 2.5 | `echo a b c d e`          | `"echo a b c d e"`            | `WORD("echo"), WORD("a"), WORD("b"), WORD("c"), WORD("d"), WORD("e"), EOF` |
| 2.6 | `echo↵`                   | `"echo\n"`                    | `WORD("echo"), NL, EOF` |
| 2.7 | `a↵b`                     | `"a\nb"`                      | `WORD("a"), NL, WORD("b"), EOF` |
| 2.8 | `a;b`                     | `"a;b"`                       | `WORD("a"), SEMI, WORD("b"), EOF` |

---

## 3. Operators (single-char and maximal munch)

| #    | Shell input | C input      | Expected tokens |
|------|-------------|--------------|-----------------|
| 3.1  | `a\|b`      | `"a\|b"`     | `WORD("a"), PIPE, WORD("b"), EOF` |
| 3.2  | `a\|\|b`    | `"a\|\|b"`   | `WORD("a"), OR_IF, WORD("b"), EOF` |
| 3.3  | `a&b`       | `"a&b"`      | `WORD("a"), AMP, WORD("b"), EOF` |
| 3.4  | `a&&b`      | `"a&&b"`     | `WORD("a"), AND_IF, WORD("b"), EOF` |
| 3.5  | `;`         | `";"`        | `SEMI, EOF` |
| 3.6  | `;;`        | `";;"`       | `DSEMI, EOF` |
| 3.7  | `;;;`       | `";;;"`      | `DSEMI, SEMI, EOF` |
| 3.8  | `\|\|\|`    | `"\|\|\|"`   | `OR_IF, PIPE, EOF` |
| 3.9  | `&&&`       | `"&&&"`      | `AND_IF, AMP, EOF` |
| 3.10 | `>>>`       | `">>>"`      | `DGREAT, GREAT, EOF` |
| 3.11 | `<<<`       | `"<<<"`      | `DLESS, LESS, EOF` (POSIX) |
| 3.12 | `(a)`       | `"(a)"`      | `LPAREN, WORD("a"), RPAREN, EOF` |
| 3.13 | `( a )`     | `"( a )"`    | `LPAREN, WORD("a"), RPAREN, EOF` |
| 3.14 | `((a))`     | `"((a))"`    | `LPAREN, LPAREN, WORD("a"), RPAREN, RPAREN, EOF` |

---

## 4. Operators terminate words without spaces

| #   | Shell input | C input     | Expected tokens |
|-----|-------------|-------------|-----------------|
| 4.1 | `cat<file`  | `"cat<file"`| `WORD("cat"), LESS, WORD("file"), EOF` |
| 4.2 | `a\|b\|c`   | `"a\|b\|c"` | `WORD("a"), PIPE, WORD("b"), PIPE, WORD("c"), EOF` |
| 4.3 | `a&&b\|\|c` | `"a&&b\|\|c"`| `WORD("a"), AND_IF, WORD("b"), OR_IF, WORD("c"), EOF` |
| 4.4 | `echo>out`  | `"echo>out"`| `WORD("echo"), GREAT, WORD("out"), EOF` |
| 4.5 | `(ls)`      | `"(ls)"`    | `LPAREN, WORD("ls"), RPAREN, EOF` |

---

## 5. Redirections

| #    | Shell input  | C input         | Expected tokens |
|------|--------------|-----------------|-----------------|
| 5.1  | `a > b`      | `"a > b"`       | `WORD("a"), GREAT, WORD("b"), EOF` |
| 5.2  | `a >> b`     | `"a >> b"`      | `WORD("a"), DGREAT, WORD("b"), EOF` |
| 5.3  | `a < b`      | `"a < b"`       | `WORD("a"), LESS, WORD("b"), EOF` |
| 5.4  | `a <> b`     | `"a <> b"`      | `WORD("a"), LESSGREAT, WORD("b"), EOF` |
| 5.5  | `a >\| b`    | `"a >\| b"`     | `WORD("a"), CLOBBER, WORD("b"), EOF` |
| 5.6  | `a >& 2`     | `"a >& 2"`      | `WORD("a"), GREATAND, WORD("2"), EOF` |
| 5.7  | `a <& 2`     | `"a <& 2"`      | `WORD("a"), LESSAND, WORD("2"), EOF` |
| 5.8  | `2>file`     | `"2>file"`      | `IO_NUMBER("2"), GREAT, WORD("file"), EOF` |
| 5.9  | `2 >file`    | `"2 >file"`     | `WORD("2"), GREAT, WORD("file"), EOF` |
| 5.10 | `a2>file`    | `"a2>file"`     | `WORD("a2"), GREAT, WORD("file"), EOF` |
| 5.11 | `10>file`    | `"10>file"`     | `IO_NUMBER("10"), GREAT, WORD("file"), EOF` |

---

## 6. Single-quote context

Reminder: SQUOTE preserves every byte literally — no escapes, no expansions.

| #    | Shell input        | C input            | Expected tokens |
|------|--------------------|--------------------|-----------------|
| 6.1  | `'hello'`          | `"'hello'"`        | `WORD("'hello'"), EOF` |
| 6.2  | `'hello world'`    | `"'hello world'"`  | `WORD("'hello world'"), EOF` |
| 6.3  | `''`               | `"''"`             | `WORD("''"), EOF` |
| 6.4  | `'a''b'`           | `"'a''b'"`         | `WORD("'a''b'"), EOF` |
| 6.5  | `'a'b'c'`          | `"'a'b'c'"`        | `WORD("'a'b'c'"), EOF` |
| 6.6  | `'a' 'b'`          | `"'a' 'b'"`        | `WORD("'a'"), WORD("'b'"), EOF` |
| 6.7  | `'a\nb'` (`\` + `n` as 2 bytes) | `"'a\\nb'"` | `WORD("'a\\nb'"), EOF` |
| 6.8  | `'a\↵b'` (`\` + real newline) | `"'a\\\nb'"` | `WORD("'a\\\nb'"), EOF` |
| 6.9  | `'$HOME'`          | `"'$HOME'"`        | `WORD("'$HOME'"), EOF` |
| 6.10 | `'a"b'`            | `"'a\"b'"`         | `WORD("'a\"b'"), EOF` |

---

## 7. Double-quote context

Reminder: DQUOTE whitelist for `\X` escapes is `$`, `` ` ``, `"`, `\`, `<newline>`.
For `X` outside this list, both bytes are preserved literally (no `\` removal at
quote removal either).

| #    | Shell input          | C input                  | Expected tokens |
|------|----------------------|--------------------------|-----------------|
| 7.1  | `"hello"`            | `"\"hello\""`            | `WORD("\"hello\""), EOF` |
| 7.2  | `"hello world"`      | `"\"hello world\""`      | `WORD("\"hello world\""), EOF` |
| 7.3  | `""`                 | `"\"\""`                 | `WORD("\"\""), EOF` |
| 7.4  | `"a""b"`             | `"\"a\"\"b\""`           | `WORD("\"a\"\"b\""), EOF` |
| 7.5  | `"a"b"c"`            | `"\"a\"b\"c\""`          | `WORD("\"a\"b\"c\""), EOF` |
| 7.6  | `"a $b c"`           | `"\"a $b c\""`           | `WORD("\"a $b c\""), EOF` |
| 7.7  | `"\$"`               | `"\"\\$\""`              | `WORD("\"\\$\""), EOF` |
| 7.8  | `"\""`               | `"\"\\\"\""`             | `WORD("\"\\\"\""), EOF` |
| 7.9  | `"\\"`               | `"\"\\\\\""`             | `WORD("\"\\\\\""), EOF` |
| 7.10 | `"\a"`               | `"\"\\a\""`              | `WORD("\"\\a\""), EOF` |
| 7.11 | `"a\↵b"` (continuation) | `"\"a\\\nb\""`        | `WORD("\"ab\""), EOF` |
| 7.12 | `"a 'b' c"`          | `"\"a 'b' c\""`          | `WORD("\"a 'b' c\""), EOF` |

---

## 8. Mixed quoting / words abutting

| #   | Shell input    | C input            | Expected tokens |
|-----|----------------|--------------------|-----------------|
| 8.1 | `a"b"c`        | `"a\"b\"c"`        | `WORD("a\"b\"c"), EOF` |
| 8.2 | `"a"'b'c`      | `"\"a\"'b'c"`      | `WORD("\"a\"'b'c"), EOF` |
| 8.3 | `"a b" c`      | `"\"a b\" c"`      | `WORD("\"a b\""), WORD("c"), EOF` |
| 8.4 | `'a b'"c d"`   | `"'a b'\"c d\""`   | `WORD("'a b'\"c d\""), EOF` |
| 8.5 | `a' 'b`        | `"a' 'b"`          | `WORD("a' 'b"), EOF` |

---

## 9. Backslash escapes (NONE context)

Reminder: in NONE, `\X` is preserved as two bytes for later quote removal,
EXCEPT `\<newline>` which is removed entirely (line continuation).

| #    | Shell input | C input      | Expected tokens |
|------|-------------|--------------|-----------------|
| 9.1  | `a\ b`      | `"a\\ b"`    | `WORD("a\\ b"), EOF` |
| 9.2  | `a\\b`      | `"a\\\\b"`   | `WORD("a\\\\b"), EOF` |
| 9.3  | `\\|`       | `"\\\|"`     | `WORD("\\\|"), EOF` |
| 9.4  | `\;`        | `"\\;"`      | `WORD("\\;"), EOF` |
| 9.5  | `\$HOME`    | `"\\$HOME"`  | `WORD("\\$HOME"), EOF` |
| 9.6  | `a\↵b`      | `"a\\\nb"`   | `WORD("ab"), EOF` |
| 9.7  | `echo a\↵b` | `"echo a\\\nb"`| `WORD("echo"), WORD("ab"), EOF` |
| 9.8  | `a\↵\↵b`    | `"a\\\n\\\nb"`| `WORD("ab"), EOF` |
| 9.9  | `\a`        | `"\\a"`      | `WORD("\\a"), EOF` |
| 9.10 | `\` (trailing) | `"\\"`    | implementation choice (bash: `WORD("\\"), EOF`; some: error) |

---

## 10. `$(...)` command substitution

Reminder: the whole `$(...)` is preserved as raw bytes in one WORD token
(possibly joined with adjacent word fragments). The recursive parser is used
internally to find the closing `)`, but the token payload contains the original
source bytes.

| #    | Shell input                       | C input                              | Expected tokens |
|------|-----------------------------------|--------------------------------------|-----------------|
| 10.1 | `$(echo hi)`                      | `"$(echo hi)"`                       | `WORD("$(echo hi)"), EOF` |
| 10.2 | `a$(b)c`                          | `"a$(b)c"`                           | `WORD("a$(b)c"), EOF` |
| 10.3 | `$(echo "a b")`                   | `"$(echo \"a b\")"`                  | `WORD("$(echo \"a b\")"), EOF` |
| 10.4 | `$(echo $(date))`                 | `"$(echo $(date))"`                  | `WORD("$(echo $(date))"), EOF` |
| 10.5 | `$(case x in *) echo;; esac)`     | `"$(case x in *) echo;; esac)"`      | `WORD("$(case x in *) echo;; esac)"), EOF` |
| 10.6 | `"$(echo hi)"`                    | `"\"$(echo hi)\""`                   | `WORD("\"$(echo hi)\""), EOF` |
| 10.7 | `'$(echo hi)'`                    | `"'$(echo hi)'"`                     | `WORD("'$(echo hi)'"), EOF` |
| 10.8 | `$()`                             | `"$()"`                              | `WORD("$()"), EOF` |
| 10.9 | `$(↵echo hi↵)`                    | `"$(\necho hi\n)"`                   | `WORD("$(\necho hi\n)"), EOF` |

---

## 11. Backticks

Backticks need no escaping in C string literals (they are not C-syntactic).

| #    | Shell input                  | C input                          | Expected tokens |
|------|------------------------------|----------------------------------|-----------------|
| 11.1 | `` `echo hi` ``              | `` "`echo hi`" ``                | `` WORD("`echo hi`"), EOF `` |
| 11.2 | `` `echo \`echo hi\`` ``     | `` "`echo \\`echo hi\\``" ``     | `` WORD("`echo \\`echo hi\\``"), EOF `` |
| 11.3 | `` `echo \$x` ``             | `` "`echo \\$x`" ``              | `` WORD("`echo \\$x`"), EOF `` |
| 11.4 | `` `echo a\↵b` ``            | `` "`echo a\\\nb`" ``            | `` WORD("`echo a\\\nb`"), EOF `` |
| 11.5 | `` a`b`c ``                  | `` "a`b`c" ``                    | `` WORD("a`b`c"), EOF `` |

---

## 12. Parameter expansion (`${...}`)

| #    | Shell input         | C input                | Expected tokens |
|------|---------------------|------------------------|-----------------|
| 12.1 | `$var`              | `"$var"`               | `WORD("$var"), EOF` |
| 12.2 | `${var}`            | `"${var}"`             | `WORD("${var}"), EOF` |
| 12.3 | `${var:-default}`   | `"${var:-default}"`    | `WORD("${var:-default}"), EOF` |
| 12.4 | `${var:-a b}`       | `"${var:-a b}"`        | `WORD("${var:-a b}"), EOF` |
| 12.5 | `${var:-"a b"}`     | `"${var:-\"a b\"}"`    | `WORD("${var:-\"a b\"}"), EOF` |
| 12.6 | `${var:-\}}`        | `"${var:-\\}}"`        | `WORD("${var:-\\}}"), EOF` |
| 12.7 | `${#var}`           | `"${#var}"`            | `WORD("${#var}"), EOF` |
| 12.8 | `${var%%pattern}`   | `"${var%%pattern}"`    | `WORD("${var%%pattern}"), EOF` |
| 12.9 | `a${b}c`            | `"a${b}c"`             | `WORD("a${b}c"), EOF` |

---

## 13. Arithmetic expansion (`$((...))`)

| #    | Shell input        | C input              | Expected tokens |
|------|--------------------|----------------------|-----------------|
| 13.1 | `$((1+2))`         | `"$((1+2))"`         | `WORD("$((1+2))"), EOF` |
| 13.2 | `$(( 1 + 2 ))`     | `"$(( 1 + 2 ))"`     | `WORD("$(( 1 + 2 ))"), EOF` |
| 13.3 | `$(($a+$b))`       | `"$(($a+$b))"`       | `WORD("$(($a+$b))"), EOF` |
| 13.4 | `$(((1+2)*3))`     | `"$(((1+2)*3))"`     | `WORD("$(((1+2)*3))"), EOF` |
| 13.5 | `a$((1))b`         | `"a$((1))b"`         | `WORD("a$((1))b"), EOF` |

---

## 14. Comments

Reminder: `#` only starts a comment when it appears at the start of a token
(i.e., preceded by blank, newline, operator, or beginning of input).

| #    | Shell input                  | C input                          | Expected tokens |
|------|------------------------------|----------------------------------|-----------------|
| 14.1 | `# just a comment`           | `"# just a comment"`             | `EOF` |
| 14.2 | `echo a # comment`           | `"echo a # comment"`             | `WORD("echo"), WORD("a"), EOF` |
| 14.3 | `echo a # comment↵echo b`    | `"echo a # comment\necho b"`     | `WORD("echo"), WORD("a"), NL, WORD("echo"), WORD("b"), EOF` |
| 14.4 | `echo a#notacomment`         | `"echo a#notacomment"`           | `WORD("echo"), WORD("a#notacomment"), EOF` |
| 14.5 | `echo "a # not comment"`     | `"echo \"a # not comment\""`     | `WORD("echo"), WORD("\"a # not comment\""), EOF` |
| 14.6 | `echo '# not comment'`       | `"echo '# not comment'"`         | `WORD("echo"), WORD("'# not comment'"), EOF` |
| 14.7 | `#comment`                   | `"#comment"`                     | `EOF` |

---

## 15. Multi-line and newline behavior

| #    | Shell input        | C input                 | Expected tokens |
|------|--------------------|-------------------------|-----------------|
| 15.1 | `echo a \↵b`       | `"echo a \\\nb"`        | `WORD("echo"), WORD("a"), WORD("b"), EOF` |
| 15.2 | `"a↵b"`            | `"\"a\nb\""`            | `WORD("\"a\nb\""), EOF` |
| 15.3 | `'a↵b'`            | `"'a\nb'"`              | `WORD("'a\nb'"), EOF` |
| 15.4 | `$(echo↵hi)`       | `"$(echo\nhi)"`         | `WORD("$(echo\nhi)"), EOF` |

---

## 16. Heredoc operator-line tokenization

These test only the **operator line** of a heredoc. Body collection is a
separate, line-oriented phase that happens after the `NL` of the operator line.

| #    | Shell input         | C input              | Expected tokens (operator line) |
|------|---------------------|----------------------|---------------------------------|
| 16.1 | `cat <<EOF`         | `"cat <<EOF"`        | `WORD("cat"), DLESS, WORD("EOF"), EOF` |
| 16.2 | `cat <<-EOF`        | `"cat <<-EOF"`       | `WORD("cat"), DLESS_DASH, WORD("EOF"), EOF` |
| 16.3 | `cat <<'EOF'`       | `"cat <<'EOF'"`      | `WORD("cat"), DLESS, WORD("'EOF'"), EOF` |
| 16.4 | `cat <<\EOF`        | `"cat <<\\EOF"`      | `WORD("cat"), DLESS, WORD("\\EOF"), EOF` |
| 16.5 | `cat <<EOF arg`     | `"cat <<EOF arg"`    | `WORD("cat"), DLESS, WORD("EOF"), WORD("arg"), EOF` |

A useful add-on test for body collection (separate from operator-line lexing):

| #     | Shell input (full) | C input | Expected body bytes |
|-------|--------------------|---------|---------------------|
| 16.6  | `cat <<EOF↵a↵b↵EOF↵` | `"cat <<EOF\na\nb\nEOF\n"` | body = `"a\nb\n"` |

---

## 17. Pipelines, lists, groups

| #    | Shell input          | C input                | Expected tokens |
|------|----------------------|------------------------|-----------------|
| 17.1 | `ls \| grep foo`     | `"ls \| grep foo"`     | `WORD("ls"), PIPE, WORD("grep"), WORD("foo"), EOF` |
| 17.2 | `a && b \|\| c`      | `"a && b \|\| c"`      | `WORD("a"), AND_IF, WORD("b"), OR_IF, WORD("c"), EOF` |
| 17.3 | `a; b; c`            | `"a; b; c"`            | `WORD("a"), SEMI, WORD("b"), SEMI, WORD("c"), EOF` |
| 17.4 | `(a; b)`             | `"(a; b)"`             | `LPAREN, WORD("a"), SEMI, WORD("b"), RPAREN, EOF` |
| 17.5 | `a & b &`            | `"a & b &"`            | `WORD("a"), AMP, WORD("b"), AMP, EOF` |
| 17.6 | `cmd > out 2>&1`     | `"cmd > out 2>&1"`     | `WORD("cmd"), GREAT, WORD("out"), IO_NUMBER("2"), GREATAND, WORD("1"), EOF` |

---

## 18. Unterminated / incomplete inputs

These should NOT return a stream ending in `EOF`. In interactive mode the
lexer signals "incomplete" and requests more input; in script mode it should
report an error at end-of-file.

| #    | Shell input              | C input                  | Expected behavior |
|------|--------------------------|--------------------------|-------------------|
| 18.1 | `'hello`                 | `"'hello"`               | unterminated SQUOTE |
| 18.2 | `"hello`                 | `"\"hello"`              | unterminated DQUOTE |
| 18.3 | `` `hello ``             | `` "`hello" ``           | unterminated BACKTICK |
| 18.4 | `$(echo`                 | `"$(echo"`               | unterminated CMD_SUB |
| 18.5 | `${var`                  | `"${var"`                | unterminated PARAM |
| 18.6 | `$((1+2)`                | `"$((1+2)"`              | unterminated ARITH |
| 18.7 | `\` (trailing backslash) | `"\\"`                   | implementation choice (see 9.10) |
| 18.8 | `$(case x in *) echo;;`  | `"$(case x in *) echo;;"`| recursive parse reports incomplete |

---

## 19. Tricky composite cases

| #    | Shell input                              | C input                                          | Expected tokens |
|------|------------------------------------------|--------------------------------------------------|-----------------|
| 19.1 | `echo "$(echo "nested")"`                | `"echo \"$(echo \"nested\")\""`                  | `WORD("echo"), WORD("\"$(echo \"nested\")\""), EOF` |
| 19.2 | `echo $(echo '$x')`                      | `"echo $(echo '$x')"`                            | `WORD("echo"), WORD("$(echo '$x')"), EOF` |
| 19.3 | `echo "${var:-"default"}"`               | `"echo \"${var:-\"default\"}\""`                 | `WORD("echo"), WORD("\"${var:-\"default\"}\""), EOF` |
| 19.4 | `echo "$((1+2))"`                        | `"echo \"$((1+2))\""`                            | `WORD("echo"), WORD("\"$((1+2))\""), EOF` |
| 19.5 | `a"b"'c'\$d$(e)${f}$((g))h`              | `"a\"b\"'c'\\$d$(e)${f}$((g))h"`                 | `WORD("a\"b\"'c'\\$d$(e)${f}$((g))h"), EOF` |
| 19.6 | `>`                                      | `">"`                                            | `GREAT, EOF` |
| 19.7 | `\|\|\|\|\|`                             | `"\|\|\|\|\|"`                                   | `OR_IF, OR_IF, PIPE, EOF` |

---

## Translation cheat sheet

When converting any new shell input into a C string literal:

| Byte you want in the shell input | C string source |
|---|---|
| `"` | `\"` |
| `\` | `\\` |
| `0x0A` (real newline, shown as `↵`) | `\n` |
| `0x09` (real tab) | `\t` |
| `'` | `'` (no escape needed) |
| `` ` `` | `` ` `` (no escape needed) |
| `$` | `$` (no escape needed in C) |
| anything else printable | as-is |

Particularly easy to confuse:
- `"\n"` is **one** newline byte (`0x0A`).
- `"\\n"` is **two** bytes: `\` and `n`.
- `"\\\n"` is **two** bytes: `\` and a real newline.
- `"\\\\"` is **two** bytes: `\` and `\`.

When in doubt, compute `strlen()` on your literal and verify it matches the
number of bytes the shell input should contain.

---

## Suggested test runner shape

```c
typedef struct {
    const char *name;
    const char *input;        /* C string passed to lex_init */
    struct {
        TokKind kind;
        const char *payload;  /* NULL for non-WORD/non-IO_NUMBER tokens */
        size_t     len;       /* 0 → use strlen(payload) */
    } expected[16];
    int expected_count;
} LexTest;

static const LexTest sq_tests[] = {
    { "6.1",  "'hello'",         { {T_WORD,"'hello'",0}, {T_EOF,NULL,0} }, 2 },
    { "6.2",  "'hello world'",   { {T_WORD,"'hello world'",0}, {T_EOF,NULL,0} }, 2 },
    /* ... */
    { "6.7",  "'a\\nb'",         { {T_WORD,"'a\\nb'",0}, {T_EOF,NULL,0} }, 2 },
    { "6.8",  "'a\\\nb'",        { {T_WORD,"'a\\\nb'",6}, {T_EOF,NULL,0} }, 2 },
    /* ... */
};

static void run_test(const LexTest *t)
{
    Lexer lx; lex_init(&lx, t->input);
    for (int i = 0; i < t->expected_count; i++) {
        Token got = lex_next(&lx);
        assert(got.kind == t->expected[i].kind);
        if (t->expected[i].payload) {
            size_t exp_len = t->expected[i].len
                ? t->expected[i].len
                : strlen(t->expected[i].payload);
            assert(got.len == exp_len);
            assert(memcmp(got.payload, t->expected[i].payload, exp_len) == 0);
        }
    }
}
```

The explicit `len` field exists because some payloads contain embedded `\0`
bytes (rare but possible in shell input), and `strlen` would underreport.
For most tests, leave `len = 0` and the runner will use `strlen`.
