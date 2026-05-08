# POSIX Shell Lexer — Implementation Guide (LLM Prompt)

> **Instructions for the LLM:**
> You are an expert in systems programming, compiler theory, and the POSIX shell specification
> (IEEE Std 1003.1-2024 / The Open Group Base Specifications Issue 8).
>
> For every section below, provide **exhaustive answers** that include:
> - A conceptual explanation grounded in the POSIX specification.
> - All relevant **edge cases and pitfalls**.
> - The exact POSIX section that governs the behaviour.
>
> The goal is to implement a **standards-conforming POSIX shell lexer** from scratch in C.
> Assume no third-party libraries except the C standard library and GNU readline for interactive input.

---

## Section 0 — Global Execution Order

> This section must be answered **first**. All subsequent sections assume the ordering
> established here. Every answer in later sections should reference the step numbers defined
> below.

**Ask the LLM:**

For TTY and none-TTY shell context:

1. Provide a **complete, numbered pipeline** of every stage a POSIX shell executes from the
   moment the user presses Enter to the moment the shell is ready to read the next command.
   For each stage state:
   - Its name and a one-sentence description.
   - Its **input type** and **output type** (e.g. `char *` → `t_token[]`).
   - Whether it runs **once per input line**, **once per token**, **once per command**, or
     **once per word** during execution.
   - The exact POSIX section that governs it.

2. Zoom in on the **lexer stage** and give the ordered list of every sub-step it performs.
   For each sub-step answer the same four questions above. The sub-steps should at minimum cover:
   - Line reading
   - Line continuation folding (`\<newline>`)
   - Line continuation characters activation and rules to respect
   - Comment stripping (`#`)
   - Operator recognition (maximal munch)
   - Quote tracking (`'`, `"`, `\`)
   - Expansion boundary detection (`$`, `` ` ``)
   - `IO_NUMBER` disambiguation
   - Token accumulation and merging
   - Heredoc operator detection (phase 1)
   - Heredoc body reading (phase 2, deferred)
   - Alias substitution

3. Zoom in on the **executor stage** and give the ordered list of every sub-step, covering at
   minimum:
   - Tilde expansion
   - Parameter expansion
   - Command substitution
   - Arithmetic expansion
   - Field splitting
   - Pathname expansion (globbing)
   - Quote removal
   - Redirection setup
   - Command lookup and execution
   - Wait and exit-status collection

4. Draw a **dependency diagram** (ASCII art or indented list) that shows which steps must
   complete before another can start, and which steps can interleave or recurse
   (e.g. command substitution causes a recursive invocation of the full pipeline).

5. Which steps are performed **inside the lexer** and which are performed **inside the
   executor**? Explain why POSIX deliberately separates recognition (lexer) from evaluation
   (executor), and what problems would arise if a shell expanded `$VAR` during tokenization.

6. When the shell encounters a **multi-line command** (open quote, open `$(`, heredoc operator,
   line continuation `\<newline>`, or keywords like `if`/`do`/`{`), at which exact step does
   it detect that more input is needed, and how does it request it (PS2, recursive read, etc.)?
   Provide the decision tree for each case.

7. When a **command substitution** `$(...)` is encountered inside a word during executor
   expansion, the full shell pipeline recurses. Describe exactly what is re-entered: is it
   only the executor, or does the shell re-run reader → lexer → parser → executor on the
   substitution body?

8. How all teh steps are connected one with the others and what is the sequence.

---
