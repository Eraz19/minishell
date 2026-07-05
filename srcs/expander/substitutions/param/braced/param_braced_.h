#ifndef PARAM_BRACED__H
# define PARAM_BRACED__H

# include "expander_.h"

/**
 * @struct s_param_exp
 * @brief Working state of a braced parameter expansion of the form
 *        ${name op word}.
 *
 * @var s_param_exp::op_char Operator applied to the parameter: '-', '=', '?'
 *                           or '+'.
 * @var s_param_exp::result_opt Quoting/context stamped onto the produced
 *                              result items.
 * @var s_param_exp::param_name Name of the parameter being expanded.
 * @var s_param_exp::param_value Current value of the parameter (empty when
 *                               unset).
 * @var s_param_exp::has_colon True for the ':op' form (test unset OR null),
 *                             false for the 'op' form (test unset only).
 * @var s_param_exp::param_is_set True when the parameter is set, even if its
 *                                value is null.
 * @var s_param_exp::operand_word The unexpanded "word" following the operator.
 * @var s_param_exp::op_span Number of items the operator spans (1 or 2); for
 *                           the '#'/'%' operators, 2 marks the greedy '##'/'%%'
 *                           form.
 */
typedef struct s_param_exp
{
	char			op_char;
	t_word_item_opt	result_opt;
	t_string		param_name;
	t_string		param_value;
	bool			has_colon;
	bool			param_is_set;
	t_word			operand_word;
	size_t			op_span;
}	t_param_exp;

/**
 * @struct s_positional_exp
 * @brief Working state of a braced positional operator form:
 *        ${@ op word} / ${* op word}.
 *
 * @var s_positional_exp::symbol The positional symbol being expanded: '@' or
 *                               '*'.
 * @var s_positional_exp::op_char Operator applied to the positional list.
 * @var s_positional_exp::result_opt Quoting/context stamped onto the produced
 *                                   result items.
 * @var s_positional_exp::operand_word The unexpanded "word" following the
 *                                     operator.
 * @var s_positional_exp::is_triggered True when there are no positional
 *                                     parameters (the operator's alternate
 *                                     branch applies).
 */
typedef struct s_positional_exp
{
	char			symbol;
	char			op_char;
	t_word_item_opt	result_opt;
	t_word			operand_word;
	bool			is_triggered;
}	t_positional_exp;

/**
 * @brief Entry point for a ${...} expansion: strips the leading "${", measures
 *        the brace body and routes to the length, positional or parameter
 *        handler.
 *
 * @param expander Expander state holding the input word at the ${ token.
 * @return The resulting error descriptor (expander->err); .type is ERR_NO on
 *         success.
 */
t_error	expand_braced(t_expander *expander);

/**
 * @brief Handles the ${name} and ${name op word} forms, dispatching to the
 *        matching operator once the name and operator have been parsed.
 *
 * @param expander Expander state positioned on the parameter name.
 * @param body_len Number of items between the braces.
 * @return The resulting error descriptor (expander->err); .type is ERR_NO on
 *         success.
 */
t_error	expand_braced_param(t_expander *expander, size_t body_len);

/**
 * @brief Handles the length forms ${#name}, ${#} and ${#@} / ${#*}.
 *
 * @param expander Expander state positioned on the '#' item.
 * @param body_len Number of items between the braces.
 * @return The resulting error descriptor (expander->err); .type is ERR_NO on
 *         success.
 */
t_error	expand_braced_length(t_expander *expander, size_t body_len);

/**
 * @brief Handles the positional forms ${@ ...} and ${* ...}.
 *
 * @param expander Expander state positioned on the '@' or '*' item.
 * @param body_len Number of items between the braces.
 * @return The resulting error descriptor (expander->err); .type is ERR_NO on
 *         success.
 */
t_error	expand_braced_positional(t_expander *expander, size_t body_len);

/**
 * @brief Applies the operator of a ${name op word} expansion, selecting the
 *        triggered branch (parameter unset, or null for a ':op' form) or the
 *        untriggered branch accordingly.
 *
 * @param expander Expander state receiving the produced result.
 * @param param_exp Fully parsed working state of the expansion.
 * @return The resulting error descriptor (expander->err); .type is ERR_NO on
 *         success.
 */
t_error	braced_dispatch(t_expander *expander, t_param_exp *param_exp);

/**
 * @brief Asserts that the current word head is the closing '}'.
 *
 * @param expander Expander state positioned where '}' is expected.
 * @return The resulting error descriptor (expander->err); .type is ERR_NO when
 *         '}' is present, ERR_PARAM_BAD_SUBSTITUTION otherwise.
 */
t_error	braced_expect_close(t_expander *expander);

/**
 * @brief Appends a computed string value to the expansion result, stamping
 *        each produced item with the given quoting/context.
 *
 * @param expander Expander state whose result word is extended.
 * @param val Value to append.
 * @param opt Quoting/context to stamp onto the produced items.
 * @return The resulting error descriptor (expander->err); .type is ERR_NO on
 *         success.
 */
t_error	braced_push_value(
			t_expander *expander,
			const t_string *val,
			t_word_item_opt opt);

/**
 * @brief Looks up a parameter's value, treating an unset parameter as an empty
 *        value rather than a fatal error.
 *
 * @param expander Expander state (its err is updated).
 * @param name Name of the parameter to look up.
 * @param out Receives the value, or an empty string when unset.
 * @return The resulting error descriptor (expander->err); .type is ERR_NO when
 *         set, ERR_NO with an empty out when unset (ERR_VAR_NOT_FOUND mapped).
 */
t_error	braced_lookup(
			t_expander *expander,
			const t_string *name,
			t_string *out);

/**
 * @brief Pushes the final value onto the result and consumes the closing '}'.
 *
 * @param expander Expander state whose result word is extended.
 * @param value Value to push (freed by this call).
 * @param opt Quoting/context to stamp onto the produced items.
 * @return The resulting error descriptor (expander->err); .type is ERR_NO on
 *         success.
 */
t_error	braced_finish(
			t_expander *expander,
			t_string *value,
			t_word_item_opt opt);

/**
 * @brief Parses the operator that follows the parameter name, handling the
 *        optional leading ':'.
 *
 * @param expander Expander state positioned on the operator.
 * @param colon Receives true when the ':op' form is used.
 * @param op Receives the operator character.
 * @param op_items Receives the number of items the operator spans (1 or 2).
 * @return The resulting error descriptor (expander->err); .type is ERR_NO on
 *         success, ERR_NOT_IMPLEMENTED for an unsupported operator.
 */
t_error	parse_braced_op(
			t_expander *expander,
			bool *colon,
			char *op,
			size_t *op_items);

/**
 * @brief Moves the first operand_len items of the input word into a freshly
 *        initialised operand word.
 *
 * @param expander Expander state whose input word is consumed.
 * @param operand_len Number of leading items to take.
 * @param operand Receives the initialised operand word.
 * @return The resulting error descriptor (expander->err); .type is ERR_NO on
 *         success.
 */
t_error	braced_take_operand(
			t_expander *expander,
			size_t operand_len,
			t_word *operand);

/**
 * @brief Recursively expands an operand word and flattens the result into a
 *        string.
 *
 * @param expander Expander state used to perform the sub-expansion.
 * @param operand Operand word to expand (freed by this call).
 * @param out Receives the flattened, expanded string.
 * @return The resulting error descriptor (expander->err); .type is ERR_NO on
 *         success.
 */
t_error	braced_operand_str(
			t_expander *expander,
			t_word *operand,
			t_string *out);

/**
 * @brief Expands the operand word and pushes the result of the expansion.
 *
 * @param expander Expander state whose result word is extended.
 * @param operand Operand word to expand (freed by this call).
 * @param opt Quoting/context to stamp onto the produced items.
 * @return The resulting error descriptor (expander->err); .type is ERR_NO on
 *         success.
 */
t_error	braced_use_operand(
			t_expander *expander,
			t_word *operand,
			t_word_item_opt opt);

/**
 * @brief Pushes the parameter's current value as the result and discards the
 *        operand word.
 *
 * @param expander Expander state whose result word is extended.
 * @param value Current value of the parameter.
 * @param opt Quoting/context to stamp onto the produced items.
 * @param operand Operand word to discard (freed by this call).
 * @return The resulting error descriptor (expander->err); .type is ERR_NO on
 *         success.
 */
t_error	braced_use_value(t_expander *expander,
			const t_string *value,
			t_word_item_opt opt,
			t_word *operand);

/**
 * @brief Assigns the expanded operand to the named variable then pushes it as
 *        the result (the '=' operator branch).
 *
 * @param expander Expander state whose result word is extended.
 * @param name Name of the variable to assign to.
 * @param opt Quoting/context to stamp onto the produced items.
 * @param operand Operand word to expand and assign (freed by this call).
 * @return The resulting error descriptor (expander->err); .type is ERR_NO on
 *         success, ERR_VAR_INVALID_NAME for a non-assignable name.
 */
t_error	braced_assign(t_expander *expander,
			const t_string *name,
			t_word_item_opt opt,
			t_word *operand);

/**
 * @brief Raises the parameter-null-or-unset error for the '?' operator,
 *        printing the operand as the message or a default one when empty.
 *
 * @param expander Expander state (its err is updated).
 * @param name Name of the unset/null parameter.
 * @param operand Operand word used as the error message (freed by this call).
 * @return The resulting error descriptor (expander->err), of type
 *         ERR_PARAM_NULL_OR_UNSET.
 */
t_error	braced_error(t_expander *expander,
			const t_string *name,
			t_word *operand);

/**
 * @brief Recursively expands an operand word into a fresh result word.
 *
 * @param expander Expander state used to perform the sub-expansion.
 * @param operand Operand word to expand (freed by this call).
 * @param out Receives the expanded word.
 * @return The resulting error descriptor (expander->err); .type is ERR_NO on
 *         success.
 */
t_error	expand_operand(t_expander *expander, t_word *operand, t_word *out);

/**
 * @brief Tells whether a character is a supported ${name op word} operator.
 *
 * @param op Candidate operator character.
 * @return true for '-', '=', '?', '+', '#' or '%', false otherwise.
 */
bool	is_valid_braced_op(char op);

/**
 * @brief Tells whether the operator at the word head is a doubled '##' / '%%'
 *        (greedy) prefix/suffix removal operator.
 *
 * @param word Input word positioned on the first operator item.
 * @param op The operator character read at index 0.
 * @return true when op is '#' or '%' and the next item repeats it.
 */
bool	braced_op_is_doubled(const t_word *word, char op);

/**
 * @brief Expands the operand word into a shell pattern string, escaping any
 *        quoted or backslash-escaped pattern metacharacter so it stays literal.
 *
 * @param expander Expander state used to perform the sub-expansion.
 * @param operand Operand word to expand (freed by this call).
 * @param out Receives the built, NUL-terminated pattern string.
 * @return The resulting error descriptor (expander->err); .type is ERR_NO on
 *         success.
 */
t_error	braced_build_pattern(
			t_expander *expander,
			t_word *operand,
			t_string *out);

/**
 * @brief Applies the '#', '##', '%' or '%%' operator: removes the matching
 *        prefix or suffix from the parameter value and pushes the result.
 *
 * @param expander Expander state whose result word is extended.
 * @param param_exp Fully parsed working state of the expansion (its operand is
 *                  freed by this call).
 * @return The resulting error descriptor (expander->err); .type is ERR_NO on
 *         success.
 */
t_error	braced_remove(t_expander *expander, t_param_exp *param_exp);

#endif
