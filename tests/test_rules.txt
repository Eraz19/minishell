This is a shel based on the POSIX IEEE Std 1003.1-2024 issue 8 specification.

The project is structured in a modular way, the modules are:
- `Scanner`: This module is responsible for reading the input from the user and breaking it down into `tokens`, `alias` expansions, `heredoc` body reading and quoting and expansion contexts management.
- `Builder`: This module is responsible for building the concret syntax tree (`CST`) from the `tokens` produced by the `Scanner` module and convert it to the final abstract syntax tree (`AST`).
- `Expander`: This module is responsible for performing `variable expansions`, `command substitutions`, and other forms of `expansion` (except the `arithmetic expansion` which is not implemented yet) as specified by the POSIX standard.
- `Runner`: This module is responsible for walking the `AST`, `redirections` creation and restoration, resolving and executing `commands` (external, builtins...).
- `Params`: This module is responsible for managing the shell's parameters, including shell `options`, `positional parameters`, `special parameters`, background `processes`, and shell `variables`.
- `Builtins`: This module is responsible for implementing the built-in commands specified by the POSIX standard (`special`, `intrinsic` and `regular` ones). The following ones are already implemented:
	- `alias`
	- `cd`
	- `unalias`
	- `wait`
	- `echo`
	- `pwd`
	- `env`
	- `readonly`
	- `colon`
	- `set`
	- `trap`
	- `exit`
	- `unset`
	- `export`

I want you to write a test for every behavior of the shell's `options`, what they do and what the posix specification says about them. The options already implemented are:
- [OK] `-a`
- [OK] `-C`
- [TD] `-e`
- [OK] `-f`
- [OK] `-h`
- [OK] `-i`
- [OK] `-n`
- [TD] `-u`
- [TD] `-v`
- [OK] `-x`
- [OK] `-c`
- [OK] `-s`
- [OK] `-o pipefail`
- [OK] `-o ignoreeof`

The OK means implemented, TD means to be done (you can write the tests but comment them out).

Then I want you to write a test suite on the shell's built-in commands, covering all the commands listed in the Built-ins module. Each test should verify the expected behavior of the command, including edge cases and error handling for all the POSIX-specified behaviors, options and arguments.

I want a test suite to cover the shell behavior for each `AST` node types, ensuring that the shell correctly interprets and executes commands according to the POSIX specification. Each test should include setup, execution, and verification steps, along with expected output and error handling.

This test suite will start with simple tests but needs to cover all the modules. When this is done, I want you to add tests for more complex scenarios, including nesting of different kinds of `AST` nodes (e.g.: a command substitution inside a function which containes redirections, the whole thing included in a pipe or a loop, etc). The goal is to ensure that the shell behaves as defined by the POSIX standard in all situations, even in very rare edge cases. So create test cases for all possible combination of shell commands (heredoc, redirections, builtins, loops, functions, expansions...).

And I also want to be able to add commands myself to the test suite easily, so please structure the tests in a way that allows for easy addition of new commands and scenarios.

For each of the tests, I want you to redirect the stdout in a file and the stderr in another file, so the tester and I can easily check the output and error messages for each test case. The test suite should also include a summary of the results, indicating which tests passed and which failed, along with any relevant error messages or output discrepancies. The output should be easily understandable and expose clearly which command was run, what was the expected stdout / stderr output and what was the obtained stdout / stderr.

You can use the `tests/test_exec` binary (see `tests/test_exec.c`) that prints the argv and envp to test their values when received by extarnal commands. You can also create other tests helpers if you need them in your tests suite.

Each test can must be runable with or without `valgrind` (the script must take and `--leak` option to activate it) and segfaults must be clearly reported in failure logs. Add a timeout system to prevent tester from blocking if shell goes in infinte loop.

VERY IMPORTANT: YOU MUST NOT TOUCH AND EDIT THE CODE OF THE SHELL
