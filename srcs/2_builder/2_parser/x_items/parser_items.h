#ifndef PARSER_ITEMS_H
# define PARSER_ITEMS_H

# include "parser.h"

# define ITEMSET_INIT_CAP	16

typedef struct s_item
{
	t_rule_id	rule;
	size_t		dot;
}	t_item;

typedef struct s_item_set
{
	t_item	*items;
	size_t	cap;
	size_t	len;
}	t_item_set;

#endif
