#ifndef MATCH_PATTERN__H
# define MATCH_PATTERN__H

# include <stddef.h>
# include <stdbool.h>

bool	ft_isxdigit(char c);
bool	match_char(char c1, char c2, size_t *len);
bool	set_negation(const char *pattern, size_t *i);
bool	valid_sub_exp_len(const char *pattern, size_t *len);

bool	eval_range(const char *pattern, char c, size_t *i);
bool	eval_sub_exp(const char *pattern, char c, size_t *i);
bool	eval_bracket_char(const char *pattern, char c, size_t *i);

bool	valid_equ_class_exp_len(const char *pattern, size_t *len);
bool	valid_char_class_exp_len(const char *pattern, size_t *len);
bool	valid_col_symbol_exp_len(const char *pattern, size_t *len);

#endif

