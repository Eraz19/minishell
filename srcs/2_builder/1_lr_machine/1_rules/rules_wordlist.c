#include "parser.h"

static void	rules_init_wordlist_1(t_rule *rules);
static void	rules_init_wordlist_2(t_rule *rules);

/*
wordlist         : wordlist WORD
                 |          WORD
                 ;
*/
void	rules_init_wordlist(t_rule *rules)
{
	rules_init_wordlist_1(rules);
	rules_init_wordlist_2(rules);
}

// wordlist -> wordlist WORD
static void	rules_init_wordlist_1(t_rule *rules)
{
	rules[RULE_WORDLIST_1].lhs = SYM_wordlist;
	rules[RULE_WORDLIST_1].rhs[0] = SYM_wordlist;
	rules[RULE_WORDLIST_1].rhs[1] = SYM_WORD;
	rules[RULE_WORDLIST_1].rhs_len = 2;
}

// wordlist -> WORD
static void	rules_init_wordlist_2(t_rule *rules)
{
	rules[RULE_WORDLIST_2].lhs = SYM_wordlist;
	rules[RULE_WORDLIST_2].rhs[0] = SYM_WORD;
	rules[RULE_WORDLIST_2].rhs_len = 1;
}
