#!/usr/bin/env zsh
###############################################################################
# Suite: CUSTOM — your scratchpad. Add cases here, they run with everything
# else (tests/test_posix_suite.zsh --suite custom to run only these).
#
# Cheat sheet — compact one-liners:
#
#   tt  ID "label" 'script' STATUS [line1 line2 ...]
#       Pipes 'script' into minishell. Asserts the exact exit STATUS and
#       that stdout is EXACTLY the given lines (no lines = empty stdout).
#
#   tth ID "label" 'script' STATUS needle...
#       Same, but stdout only has to CONTAIN each needle.
#
#   tte ID "label" 'script' STATUS|'!0' err_needle [line...]
#       Also checks the (debug-filtered) stderr contains err_needle.
#
#   tta ID "label" STATUS out_needle -- argv...
#       Runs `minishell argv...` (e.g. -c '...', a script file, flags).
#
# Full control:
#
#   t_begin MY-1 "what it should do"
#   t_setup 'touch fixture.txt'          # host-side setup, runs in the workdir
#   T_ENV=(-u HOME LC_ALL=C)             # optional env for this run
#   t_run 'echo hi'                      # or: t_run_argv -c 'echo hi'
#   expect_status 0                      # expect_status_nonzero
#   expect_lines "hi"                    # exact stdout; expect_out_exact "hi"
#   expect_out_contains "h"              # expect_out_lacks / expect_err_*
#   expect_file_lines fixture.txt        # file content in the workdir
#   t_end
#
# Every case runs in its own empty working directory and logs to
# tests/logs/posix_suite.N/<ID>/report.txt (plus raw stdout/stderr files).
# $TEST_EXEC is the argv/envp echo helper (tests/test_exec).
###############################################################################

t_section "custom cases"

tt CUSTOM.1 "example: exact stdout" \
'echo hello' 0 "hello"

tth CUSTOM.2 "example: stdout contains" \
'env' 0 "PATH="

t_begin CUSTOM.3 "example: full API with a fixture file"
t_setup 'printf "line_a\n" > seed.txt'
t_run 'cat seed.txt'
expect_status 0
expect_lines "line_a"
t_end
