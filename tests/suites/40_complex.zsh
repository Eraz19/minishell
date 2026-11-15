#!/usr/bin/env zsh
###############################################################################
# Suite: COMPLEX nesting — combinations of AST nodes, expansions,
# redirections, heredocs, functions, loops and pipes (test_rules.txt §complex)
#
# Naming: NEST-<n> for structural nesting, MIX-<n> for feature interactions.
###############################################################################

###############################################################################
t_section "nesting: command substitution deep inside structures"
###############################################################################

tt NEST.1 "cmd-sub inside a function body" \
'f() { echo got:$(echo inner); }
f' 0 "got:inner"

tt NEST.2 "nested command substitutions" \
'echo $(echo $(echo deepest))' 0 "deepest"

tt NEST.3 "cmd-sub inside an if condition" \
'if test "$(echo yes)" = yes; then echo matched; fi' 0 "matched"

tt NEST.4 "cmd-sub feeds a for word list" \
'for w in $(printf "a\nb\n"); do echo w=$w; done' 0 "w=a" "w=b"

tt NEST.5 "cmd-sub inside a case word and a pattern arm" \
'case $(echo key) in key) echo hit;; esac' 0 "hit"

tt NEST.6 "cmd-sub inside a heredoc body inside a function" \
'f() { cat <<EOF
val=$(echo generated)
EOF
}
f' 0 "val=generated"

tt NEST.7 "function with redirection, called inside a pipeline (rules example)" \
'f() { echo piped_out > inner.txt; cat inner.txt; }
f | cat' 0 "piped_out"

tt NEST.8 "cmd-sub + redirection + function, all inside a loop" \
'f() { echo one_$(echo shot) > gen.txt; }
for i in 1 2; do
	f
	cat gen.txt
done' 0 "one_shot" "one_shot"

tt NEST.9 "subshell inside a pipeline" \
'(echo from_subshell; exit 0) | cat' 0 "from_subshell"

tt NEST.10 "pipeline inside a subshell inside &&" \
'true && (echo x | tr x y)' 0 "y"

###############################################################################
t_section "nesting: control structures inside each other"
###############################################################################

tt NEST.11 "if inside a for inside a while" \
'while true; do
	for i in 1 2 3; do
		if test $i = 2; then echo found_$i; fi
	done
	break
done' 0 "found_2"

tt NEST.12 "case inside a for" \
'for x in a b c; do
	case $x in
		a) echo first;;
		c) echo last;;
	esac
done' 0 "first" "last"

tt NEST.13 "for inside a function inside a pipeline" \
'f() { for i in p q; do echo $i; done; }
f | sort -r' 0 "q" "p"

tt NEST.14 "heredoc on a loop inside a function" \
'f() {
	while true; do
		cat
		break
	done <<EOF
u
v
EOF
}
f' 0 "u" "v"

tt NEST.15 "brace group inside if inside subshell" \
'(if true; then { echo a; echo b; }; fi)' 0 "a" "b"

tt NEST.16 "function defined inside an if, then called" \
'if true; then
	late_f() { echo defined_late; }
fi
late_f' 0 "defined_late"

tt NEST.17 "loop over a pipeline of and-ors" \
'for i in 1 2; do
	false || echo rescued_$i
done | cat' 0 "rescued_1" "rescued_2"

tt NEST.18 "nested functions calling each other" \
'inner() { echo core; }
outer() { inner; }
outer' 0 "core"

tt NEST.19 "recursion terminated by a test" \
'countdown() {
	if test "$1" = 1; then
		echo lvl$1
		countdown 2
	elif test "$1" = 2; then
		echo lvl$1
	fi
}
countdown 1' 0 "lvl1" "lvl2"

###############################################################################
t_section "mixing: redirections + heredocs + expansions + pipes"
###############################################################################

tt MIX.1 "if with redirected output inside a pipe" \
'if true; then echo branch_out; fi > mid.txt
cat mid.txt | tr a-z A-Z' 0 "BRANCH_OUT"

tt MIX.2 "heredoc into a pipeline stage" \
'cat <<EOF | sort
b
a
EOF' 0 "a" "b"

tt MIX.3 "expansion result used as a redirection target inside a loop" \
'for name in t1 t2; do
	echo data_$name > out_$name.txt
done
cat out_t1.txt out_t2.txt' 0 "data_t1" "data_t2"

tt MIX.4 "glob feeding a for, writing per-file, checked by cat" \
'touch s1.src s2.src
for f in *.src; do echo seen:$f >> report.txt; done
cat report.txt' 0 "seen:s1.src" "seen:s2.src"

tt MIX.5 "alias expanding to a pipeline head" \
"alias upper='tr a-z A-Z'
echo mixed | upper" 0 "MIXED"

tt MIX.6 "assignment prefix + redirection + external in one command" \
'MIXV=6 '"$TEST_EXEC"' > /dev/null 2> caught.txt
grep -c "MIXV=6" caught.txt' 0 "1"

t_begin MIX.7 "cmd-sub of a pipeline of a heredoc"
t_run 'R=$(cat <<EOF | wc -l
1
2
3
EOF
)
echo lines=$R'
expect_status 0
T_EXP_OUT_FILE="${T_LOG}/stdout.expected.txt"
printf '%s\n' "lines= 3" > "$T_EXP_OUT_FILE"
printf '%s\n' "lines=3" > "${T_LOG}/stdout.expected.alt.txt"
if ! cmp -s "$T_EXP_OUT_FILE" "$T_OUT_FILE" \
	&& ! cmp -s "${T_LOG}/stdout.expected.alt.txt" "$T_OUT_FILE"; then
	t_fail "stdout: differs from expected alternatives (see report)"
fi
t_end

tt MIX.8 "case on a cmd-sub over a glob, with redirected arm" \
'touch only_one.m8
case $(echo *.m8) in
	only_one.m8) echo matched > arm.txt;;
esac
cat arm.txt' 0 "matched"

tt MIX.9 "background subshell writing a file, reaped by wait" \
'(echo async_done > bg.txt) &
wait
cat bg.txt' 0 "async_done"

tt MIX.10 "pipeline of two functions with heredoc input" \
'produce() { cat <<EOF
raw
EOF
}
consume() { tr a-z A-Z; }
produce | consume' 0 "RAW"

tt MIX.11 "IFS-driven field splitting of a cmd-sub inside a for" \
'IFS=:
for part in $(echo a:b:c); do echo p=$part; done' 0 "p=a" "p=b" "p=c"

t_begin MIX.12 "quoted \"\$@\" forwarding through a function into exec"
t_run 'f() { '"$TEST_EXEC"' "$@"; }
f "one word" two'
expect_status 0
expect_err_contains "argv[1] => [one word]"
expect_err_contains "argv[2] => [two]"
t_end

tt MIX.13 "exit status flows through nesting: function > if > pipeline" \
'f() { if true; then sh -c "exit 8"; fi; }
f
echo rc=$?' 0 "rc=8"

t_begin MIX.14 "\${RO:=word} on a readonly NULL var -> assignment error 124, shell exits"
t_run 'readonly LOCK_14=
echo ${LOCK_14:=other}
echo not_reached'
expect_status 124
expect_out_lacks "not_reached"
t_end

tt MIX.15 "set -f inside a function affects the caller (shared options)" \
'f() { set -f; }
touch g.m15
f
echo *.m15' 0 "*.m15"

###############################################################################
t_section "stress: deeper combinations"
###############################################################################

tt STRESS.1 "4-deep structure: while(for(if(case)))" \
'while true; do
	for i in hit miss; do
		if true; then
			case $i in hit) echo case_$i;; esac
		fi
	done
	break
done' 0 "case_hit"

tt STRESS.2 "pipeline where every stage is a compound command" \
'{ echo b; echo a; } | (sort) | if true; then cat; fi' \
0 "a" "b"

tt STRESS.3 "10-stage pipeline" \
'echo start | cat | cat | cat | cat | cat | cat | cat | cat | cat' \
0 "start"

tt STRESS.4 "long && chain with a || fallback at each level" \
'true && true && false || echo lvl1
true && { false || echo lvl2; }' 0 "lvl1" "lvl2"

tt STRESS.5 "function redefining itself on first call" \
'once() { once() { echo second; }; echo first; }
once
once' 0 "first" "second"

tt STRESS.6 "heredoc + quoted delim + expansion mix in one script" \
'V=live
cat <<E1
exp=$V
E1
cat <<'"'"'E2'"'"'
raw=$V
E2' 0 "exp=live" 'raw=$V'

tt STRESS.7 "async loop + foreground loop interleaved via wait" \
'for i in 1 2; do echo bg_$i >> bg.txt; done &
for i in 1 2; do echo fg_$i >> fg.txt; done
wait
sort bg.txt fg.txt' 0 "bg_1" "bg_2" "fg_1" "fg_2"

tt STRESS.8 "cmd-sub inside function inside cmd-sub" \
'f() { echo $(echo nested_f); }
echo top:$(f)' 0 "top:nested_f"
