# Section 18 (expanded): Unterminated contexts & multi-chunk continuation

Companion to the main lexer test suite. Every step shows the **full** state
of the `t_lexer` struct after the call to `lex_next_token` returns.

## Lexer struct under test

```c
typedef struct s_lexer
{
    size_t      i;
    t_ctx_stack ctx;                    /* { len, size, data[] } */
    char       *input;
    char       *script_path;
    size_t      total_removed_count;
    size_t      current_removed_count;
} t_lexer;
```

## State block format

After every `lex_next_token` call, the state is shown as:

```
input                 = <C-string literal of the current bytes>
i                     = <byte index>
ctx.len               = <stack depth>
ctx.data[0..len-1]    = [<oldest>, ..., <newest>]
total_removed_count   = <N>
current_removed_count = <N>
result                = LEX_OK | LEX_INCOMPLETE | LEX_EOF
token emitted         = <WORD/EOF/...> | (none)
```

Each ctx entry: `{TYPE, depth=N}`. `depth` is only meaningful for
`CMD_SUB`, `ARITH`, `PARAM` (paren/brace counting); for `SQUOTE`,
`DQUOTE`, `BACKTICK` it stays at 0.

`script_path` stays `NULL` in every test (in-memory inputs only), so I
omit it from each state block. Add `assert(lexer.script_path == NULL)`
once at the top of your runner.

`ctx.size` is implementation-defined capacity; the only invariant is
`ctx.size >= ctx.len`. I omit it for the same reason.

For multi-chunk tests, between steps the harness appends bytes to
`lexer.input` and does NOT touch `i` or `ctx`.

---

## Part A: Original 18.x cases (single-chunk)

### 18.1 — `'hello` (unterminated SQUOTE)

Initial: `input = "'hello"` (6 bytes)

**Step 1**: call `lex_next_token`

```
input                 = "'hello"
i                     = 6
ctx.len               = 1
ctx.data[0]           = {SQUOTE, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

---

### 18.2 — `"hello` (unterminated DQUOTE)

Initial: `input = "\"hello"` (6 bytes)

**Step 1**: call `lex_next_token`

```
input                 = "\"hello"
i                     = 6
ctx.len               = 1
ctx.data[0]           = {DQUOTE, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

---

### 18.3 — `` `hello `` (unterminated BACKTICK)

Initial: `` input = "`hello" `` (6 bytes)

**Step 1**: call `lex_next_token`

```
input                 = "`hello"
i                     = 6
ctx.len               = 1
ctx.data[0]           = {BACKTICK, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

---

### 18.4 — `$(echo` (unterminated CMD_SUB)

Initial: `input = "$(echo"` (6 bytes)

**Step 1**: call `lex_next_token`

```
input                 = "$(echo"
i                     = 6
ctx.len               = 1
ctx.data[0]           = {CMD_SUB, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

---

### 18.5 — `${var` (unterminated PARAM)

Initial: `input = "${var"` (5 bytes)

**Step 1**: call `lex_next_token`

```
input                 = "${var"
i                     = 5
ctx.len               = 1
ctx.data[0]           = {PARAM, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

---

### 18.6 — `$((1+2)` (unterminated ARITH)

Initial: `input = "$((1+2)"` (7 bytes)

**Step 1**: call `lex_next_token`

```
input                 = "$((1+2)"
i                     = 7
ctx.len               = 1
ctx.data[0]           = {ARITH, depth=0}    /* see note below */
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

Note: `depth` represents internal `(`/`)` balance inside ARITH. Opening
`$((` enters the context with depth=0; the lexer needs a `))` pair to
close it. The single `)` at i=6 is one of two needed; the second is
missing. Whether your implementation flips depth to -1, leaves it at 0,
or tracks a separate "saw one closer" flag is up to you. The hard
requirement is that `ctx.data[0].type == ARITH` after step 1.

---

### 18.7 — `\` at EOF (trailing backslash)

Initial: `input = "\\"` (1 byte)

POSIX leaves this unspecified. Pick ONE behavior:

#### Option (a) — bash style, backslash is literal

**Step 1**: call `lex_next_token`

```
input                 = "\\"
i                     = 1
ctx.len               = 0
total_removed_count   = 0
current_removed_count = 0
result                = LEX_OK
token emitted         = WORD("\\")        /* 1 byte: a single backslash */
```

**Step 2**: call `lex_next_token`

```
input                 = "\\"
i                     = 1
ctx.len               = 0
total_removed_count   = 0
current_removed_count = 0
result                = LEX_EOF
token emitted         = (none)
```

#### Option (b) — wait for continuation (requires extra struct field)

**Step 1**: call `lex_next_token`

```
input                 = "\\"
i                     = 1
ctx.len               = 0
pending_continuation  = true              /* NEW field you'd need to add */
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

Recommendation: go with (a). Your current struct doesn't have a
`pending_continuation` flag, and option (b) buys little over (a). However,
see 18.24 — without it, continuations can't span chunk boundaries.

---

### 18.8 — `$(case x in *) echo;;` (CMD_SUB with incomplete case)

Initial: `input = "$(case x in *) echo;;"` (21 bytes)

**Step 1**: call `lex_next_token`

```
input                 = "$(case x in *) echo;;"
i                     = 21
ctx.len               = 1
ctx.data[0]           = {CMD_SUB, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

Note: from the outer lexer's perspective this state is identical to 18.4.
The "incompleteness" lives inside the recursive sub-parser (mid-`case`
waiting for `esac`). Outer lexer-only assertions can't distinguish them.

---

## Part B: Multi-chunk continuation

Each test below proceeds in numbered **Rounds**. For every round:

1. **APPEND** — the C-string bytes to concatenate onto the *current*
   `lexer.input`. Round 1 starts from empty, so its "APPEND" is the
   initial input.
2. **INPUT IS NOW** — the full content of `lexer.input` after the append.
3. **Call `lex_next_token`** and check the state block.

The harness should NEVER reset `i`, `ctx`, or the removed counters
between rounds — only `input` grows.

---

### 18.9 — SQUOTE completed across two chunks

**Final assembled input:** `"'ab'"` (4 bytes total)

#### Round 1
- **APPEND:** `"'a"` (2 bytes)
- **`lexer.input` is now:** `"'a"` (2 bytes)
- Call `lex_next_token`. State after:

```
input                 = "'a"
i                     = 2
ctx.len               = 1
ctx.data[0]           = {SQUOTE, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

#### Round 2
- **APPEND:** `"b'"` (2 bytes)
- **`lexer.input` is now:** `"'ab'"` (4 bytes)
- Call `lex_next_token`. State after:

```
input                 = "'ab'"
i                     = 4
ctx.len               = 0
total_removed_count   = 0
current_removed_count = 0
result                = LEX_OK
token emitted         = WORD("'ab'")
```

#### Round 3 (sanity check — no new bytes)
- **APPEND:** nothing (0 bytes)
- **`lexer.input` is now:** `"'ab'"` (4 bytes)
- Call `lex_next_token`. State after:

```
input                 = "'ab'"
i                     = 4
ctx.len               = 0
total_removed_count   = 0
current_removed_count = 0
result                = LEX_EOF
token emitted         = (none)
```

---

### 18.10 — DQUOTE completed across two chunks

**Final assembled input:** `"\"a$b\""` (5 bytes total)

#### Round 1
- **APPEND:** `"\"a"` (2 bytes)
- **`lexer.input` is now:** `"\"a"` (2 bytes)
- Call `lex_next_token`. State after:

```
input                 = "\"a"
i                     = 2
ctx.len               = 1
ctx.data[0]           = {DQUOTE, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

#### Round 2
- **APPEND:** `"$b\""` (3 bytes)
- **`lexer.input` is now:** `"\"a$b\""` (5 bytes)
- Call `lex_next_token`. State after:

```
input                 = "\"a$b\""
i                     = 5
ctx.len               = 0
total_removed_count   = 0
current_removed_count = 0
result                = LEX_OK
token emitted         = WORD("\"a$b\"")
```

---

### 18.11 — BACKTICK completed across two chunks

**Final assembled input:** `` "`echo hi`" `` (9 bytes total)

#### Round 1
- **APPEND:** `` "`echo " `` (6 bytes)
- **`lexer.input` is now:** `` "`echo " `` (6 bytes)
- Call `lex_next_token`. State after:

```
input                 = "`echo "
i                     = 6
ctx.len               = 1
ctx.data[0]           = {BACKTICK, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

#### Round 2
- **APPEND:** `` "hi`" `` (3 bytes)
- **`lexer.input` is now:** `` "`echo hi`" `` (9 bytes)
- Call `lex_next_token`. State after:

```
input                 = "`echo hi`"
i                     = 9
ctx.len               = 0
total_removed_count   = 0
current_removed_count = 0
result                = LEX_OK
token emitted         = WORD("`echo hi`")
```

---

### 18.12 — CMD_SUB completed across two chunks

**Final assembled input:** `"$(echo hi)"` (10 bytes total)

#### Round 1
- **APPEND:** `"$(echo"` (6 bytes)
- **`lexer.input` is now:** `"$(echo"` (6 bytes)
- Call `lex_next_token`. State after:

```
input                 = "$(echo"
i                     = 6
ctx.len               = 1
ctx.data[0]           = {CMD_SUB, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

#### Round 2
- **APPEND:** `" hi)"` (4 bytes)
- **`lexer.input` is now:** `"$(echo hi)"` (10 bytes)
- Call `lex_next_token`. State after:

```
input                 = "$(echo hi)"
i                     = 10
ctx.len               = 0
total_removed_count   = 0
current_removed_count = 0
result                = LEX_OK
token emitted         = WORD("$(echo hi)")
```

---

### 18.13 — PARAM completed across two chunks

**Final assembled input:** `"${var:-def}"` (11 bytes total)

#### Round 1
- **APPEND:** `"${var"` (5 bytes)
- **`lexer.input` is now:** `"${var"` (5 bytes)
- Call `lex_next_token`. State after:

```
input                 = "${var"
i                     = 5
ctx.len               = 1
ctx.data[0]           = {PARAM, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

#### Round 2
- **APPEND:** `":-def}"` (6 bytes)
- **`lexer.input` is now:** `"${var:-def}"` (11 bytes)
- Call `lex_next_token`. State after:

```
input                 = "${var:-def}"
i                     = 11
ctx.len               = 0
total_removed_count   = 0
current_removed_count = 0
result                = LEX_OK
token emitted         = WORD("${var:-def}")
```

---

### 18.14 — ARITH completed across two chunks

**Final assembled input:** `"$((1+2))"` (8 bytes total)

#### Round 1
- **APPEND:** `"$((1+2"` (6 bytes)
- **`lexer.input` is now:** `"$((1+2"` (6 bytes)
- Call `lex_next_token`. State after:

```
input                 = "$((1+2"
i                     = 6
ctx.len               = 1
ctx.data[0]           = {ARITH, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

#### Round 2
- **APPEND:** `"))"` (2 bytes)
- **`lexer.input` is now:** `"$((1+2))"` (8 bytes)
- Call `lex_next_token`. State after:

```
input                 = "$((1+2))"
i                     = 8
ctx.len               = 0
total_removed_count   = 0
current_removed_count = 0
result                = LEX_OK
token emitted         = WORD("$((1+2))")
```

---

### 18.15 — SQUOTE completed in three chunks

**Final assembled input:** `"'ab'"` (4 bytes total)

This test breaks the same input as 18.9 into three rounds to verify the
lexer can survive multiple consecutive INCOMPLETE returns inside the
same open context.

#### Round 1
- **APPEND:** `"'a"` (2 bytes)
- **`lexer.input` is now:** `"'a"` (2 bytes)
- Call `lex_next_token`. State after:

```
input                 = "'a"
i                     = 2
ctx.len               = 1
ctx.data[0]           = {SQUOTE, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

#### Round 2
- **APPEND:** `"b"` (1 byte)
- **`lexer.input` is now:** `"'ab"` (3 bytes)
- Call `lex_next_token`. State after:

```
input                 = "'ab"
i                     = 3
ctx.len               = 1
ctx.data[0]           = {SQUOTE, depth=0}    /* SAME as round 1 */
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

#### Round 3
- **APPEND:** `"'"` (1 byte)
- **`lexer.input` is now:** `"'ab'"` (4 bytes)
- Call `lex_next_token`. State after:

```
input                 = "'ab'"
i                     = 4
ctx.len               = 0
total_removed_count   = 0
current_removed_count = 0
result                = LEX_OK
token emitted         = WORD("'ab'")
```

**Key invariant:** between rounds 1 and 2 the context stack is identical
(SQUOTE still on top). Only `i` and `input` change. The lexer must not
push or pop the SQUOTE while still inside the unfinished string.

---

### 18.16 — Empty continuation chunk

**Final assembled input:** `"\"abc\""` (5 bytes total)

This test verifies the lexer handles a zero-byte append (which can happen
when readline returns an empty line) without corrupting its state.

#### Round 1
- **APPEND:** `"\"abc"` (4 bytes)
- **`lexer.input` is now:** `"\"abc"` (4 bytes)
- Call `lex_next_token`. State after:

```
input                 = "\"abc"
i                     = 4
ctx.len               = 1
ctx.data[0]           = {DQUOTE, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

#### Round 2
- **APPEND:** `""` (0 bytes — empty append)
- **`lexer.input` is now:** `"\"abc"` (still 4 bytes)
- Call `lex_next_token`. State after:

```
input                 = "\"abc"
i                     = 4
ctx.len               = 1
ctx.data[0]           = {DQUOTE, depth=0}     /* identical to round 1 */
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

#### Round 3
- **APPEND:** `"\""` (1 byte)
- **`lexer.input` is now:** `"\"abc\""` (5 bytes)
- Call `lex_next_token`. State after:

```
input                 = "\"abc\""
i                     = 5
ctx.len               = 0
total_removed_count   = 0
current_removed_count = 0
result                = LEX_OK
token emitted         = WORD("\"abc\"")
```

The lexer must handle "no new bytes since last call" gracefully — call
again, get INCOMPLETE again, no spurious state changes.

---

## Part C: Nested-context unfinished cases

### 18.17 — DQUOTE inside CMD_SUB, both unfinished

Initial: `input = "$(\"abc"` (6 bytes).

**Step 1**: lex

```
input                 = "$(\"abc"
i                     = 6
ctx.len               = 2
ctx.data[0]           = {CMD_SUB, depth=0}     /* bottom of stack */
ctx.data[1]           = {DQUOTE,  depth=0}     /* top of stack */
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

If your design uses a separate sub-lexer instance for `$(...)` rather
than a shared stack, then the outer lexer has `ctx.len = 1,
ctx.data[0] = CMD_SUB` and the inner sub-lexer has its own
`ctx.len = 1, ctx.data[0] = DQUOTE`. Match your implementation.

---

### 18.18 — CMD_SUB inside DQUOTE, both unfinished

Initial: `input = "\"$(echo"` (7 bytes).

**Step 1**: lex

```
input                 = "\"$(echo"
i                     = 7
ctx.len               = 2
ctx.data[0]           = {DQUOTE,  depth=0}
ctx.data[1]           = {CMD_SUB, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

---

### 18.19 — Nested CMD_SUB, inner unfinished

Initial: `input = "$(echo $(date"` (13 bytes).

**Step 1**: lex

```
input                 = "$(echo $(date"
i                     = 13
ctx.len               = 2
ctx.data[0]           = {CMD_SUB, depth=0}     /* outer $( at i=0..1  */
ctx.data[1]           = {CMD_SUB, depth=0}     /* inner $( at i=7..8  */
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

---

### 18.20 — DQUOTE inside PARAM, both unfinished

Initial: `input = "${var:-\"abc"` (11 bytes).

**Step 1**: lex

```
input                 = "${var:-\"abc"
i                     = 11
ctx.len               = 2
ctx.data[0]           = {PARAM,  depth=0}
ctx.data[1]           = {DQUOTE, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

---

### 18.21 — ARITH with internal `(` (nesting_depth check)

Initial: `input = "$(((1+2"` (7 bytes).

**Step 1**: lex

```
input                 = "$(((1+2"
i                     = 7
ctx.len               = 1
ctx.data[0]           = {ARITH, depth=1}       /* extra ( at i=3 raised depth */
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

This is the only test where `nesting_depth != 0` for an open context.
Verify: opening `$((` enters ARITH with depth=0; the third `(` at i=3
raises depth to 1; `1+2` doesn't touch it. The closer needs depth back
to 0 AND a final `))` pair.

---

### 18.22 — Nested DQUOTE-inside-CMD_SUB completed across chunks

Chunk 1: `"$(\"a"` (4 bytes). Chunk 2: `"b\")"` (4 bytes → `"$(\"ab\")"`, 8 bytes).

**Step 1**: lex

```
input                 = "$(\"a"
i                     = 4
ctx.len               = 2
ctx.data[0]           = {CMD_SUB, depth=0}
ctx.data[1]           = {DQUOTE,  depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

**Step 2**: lex (after append)

```
input                 = "$(\"ab\")"
i                     = 8
ctx.len               = 0                       /* both contexts popped */
total_removed_count   = 0
current_removed_count = 0
result                = LEX_OK
token emitted         = WORD("$(\"ab\")")       /* 8 bytes */
```

Between steps the stack stays at length 2; in step 2 the DQUOTE pops on
the `"` at i=6 and the CMD_SUB pops on the `)` at i=7.

---

## Part D: Line-continuation interactions

These exercise `total_removed_count` and `current_removed_count`.

### 18.23 — `echo \<newline>hi` (continuation inside one input)

Initial: `input = "echo \\\nhi"` — 9 bytes:
`e`(0) `c`(1) `h`(2) `o`(3) ` `(4) `\`(5) `0x0A`(6) `h`(7) `i`(8).

**Step 1**: lex

```
input                 = "echo \\\nhi"
i                     = 4
ctx.len               = 0
total_removed_count   = 0
current_removed_count = 0
result                = LEX_OK
token emitted         = WORD("echo")            /* 4 bytes */
```

**Step 2**: lex (skips `\<newline>` at i=5..6, then reads `hi`)

```
input                 = "echo \\\nhi"
i                     = 9
ctx.len               = 0
total_removed_count   = 2                       /* the \<nl> pair */
current_removed_count = 2                       /* removed while building this token */
result                = LEX_OK
token emitted         = WORD("hi")              /* 2 bytes */
```

**Step 3**: lex

```
input                 = "echo \\\nhi"
i                     = 9
ctx.len               = 0
total_removed_count   = 2
current_removed_count = 0                       /* OR 2, depending on reset rule */
result                = LEX_EOF
token emitted         = (none)
```

Implementation choice: does `current_removed_count` reset at the **start**
of a new tokenization step (so step 3 shows 0) or only when the **next**
token is actually being built (so step 3 still shows 2)? Pick one and
document it. I show 0 here under the "reset at start of next call" rule.

---

### 18.24 — Continuation across a chunk boundary

Chunk 1: `"echo \\"` (5 bytes). Chunk 2: `"\nhi"` (3 bytes → `"echo \\\nhi"`, 9 bytes).

**Step 1**: lex

```
input                 = "echo \\"
i                     = 4
ctx.len               = 0
total_removed_count   = 0
current_removed_count = 0
result                = LEX_OK
token emitted         = WORD("echo")
```

**Step 2**: lex (input still 5 bytes; need to decide what trailing `\` means)

Under option (a) from 18.7 (trailing `\` is literal):

```
input                 = "echo \\"
i                     = 5
ctx.len               = 0
total_removed_count   = 0
current_removed_count = 0
result                = LEX_OK
token emitted         = WORD("\\")              /* 1 byte! WRONG for continuation */
```

That's a real downside of option (a) — it can't span the boundary.

Under option (b):

```
input                 = "echo \\"
i                     = 5
ctx.len               = 0
pending_continuation  = true
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

**Step 3**: lex (after append `"\nhi"`), under option (b):

```
input                 = "echo \\\nhi"
i                     = 9
ctx.len               = 0
pending_continuation  = false
total_removed_count   = 2
current_removed_count = 2
result                = LEX_OK
token emitted         = WORD("hi")
```

This is the strongest argument for option (b). If you want correct
line-continuation across chunk boundaries (normal interactive behavior),
you need that extra flag.

---

### 18.25 — Continuation inside DQUOTE, across chunks

Chunk 1: `"\"a\\"` (3 bytes). Chunk 2: `"\nb\""` (3 bytes → `"\"a\\\nb\""`, 6 bytes).

**Step 1**: lex

```
input                 = "\"a\\"
i                     = 3
ctx.len               = 1
ctx.data[0]           = {DQUOTE, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

The DQUOTE context alone makes this INCOMPLETE regardless of your
trailing-`\` choice from 18.7 — the lexer is still mid-string.

**Step 2**: lex (after append)

```
input                 = "\"a\\\nb\""
i                     = 6
ctx.len               = 0
total_removed_count   = 2                       /* \<nl> removed inside DQUOTE */
current_removed_count = 2
result                = LEX_OK
token emitted         = WORD("\"ab\"")          /* 4 bytes — \<nl> vanished */
```

The token payload is 4 bytes (`"`, `a`, `b`, `"`), not 6 — DQUOTE's
escape whitelist includes `\<newline>`.

---

### 18.26 — Same input as 18.25 but with SQUOTE

Chunk 1: `"'a\\"` (3 bytes). Chunk 2: `"\nb'"` (3 bytes → `"'a\\\nb'"`, 6 bytes).

**Step 1**: lex

```
input                 = "'a\\"
i                     = 3
ctx.len               = 1
ctx.data[0]           = {SQUOTE, depth=0}
total_removed_count   = 0
current_removed_count = 0
result                = LEX_INCOMPLETE
token emitted         = (none)
```

**Step 2**: lex (after append)

```
input                 = "'a\\\nb'"
i                     = 6
ctx.len               = 0
total_removed_count   = 0                       /* SQUOTE preserves \<nl> literally */
current_removed_count = 0
result                = LEX_OK
token emitted         = WORD("'a\\\nb'")        /* full 6 bytes preserved */
```

Critical contrast with 18.25: same input shape, but because SQUOTE has
no escape processing, the `\<newline>` survives as two literal bytes and
the removed counters stay at 0.

---

## Invariants worth asserting on every test

For any call returning `LEX_INCOMPLETE`:

```c
assert(lexer.i == strlen(lexer.input));     /* consumed everything received */
assert(lexer.ctx.len > 0
       || lexer.pending_continuation);      /* some open construct must exist */
                                            /* (drop the || if you chose option a) */
assert(lexer.script_path == NULL);          /* in-memory test only */
assert(lexer.ctx.size >= lexer.ctx.len);    /* capacity invariant */
```

For any call returning `LEX_OK` (token emitted) after a previous INCOMPLETE:

```c
assert(lexer.i > prev_i);                                /* advanced */
assert(lexer.total_removed_count
       >= prev_total_removed);                           /* monotonic */
/* For top-level tokens (not inside other open contexts): */
/* assert(lexer.ctx.len == 0);                             */
```

For any call returning `LEX_EOF`:

```c
assert(lexer.i == strlen(lexer.input));
assert(lexer.ctx.len == 0);
assert(!lexer.pending_continuation);        /* if you have that field */
```