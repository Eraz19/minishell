#ifndef MATCH_PATTERN__H
# define MATCH_PATTERN__H

# include <stddef.h>
# include <stdbool.h>

bool	match_char(char c1, char c2, size_t *len);
bool	match_pattern(const char *pattern, const char *str);
bool	valid_sub_exp_len(const char *pattern, size_t *len);

bool	valid_equ_class_exp_len(const char *pattern, size_t *len);
bool	valid_char_class_exp_len(const char *pattern, size_t *len);
bool	valid_col_symbol_exp_len(const char *pattern, size_t *len);

#endif
