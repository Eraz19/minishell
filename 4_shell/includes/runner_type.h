/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner_type.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:23:31 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:23:32 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNNER_TYPE_H
# define RUNNER_TYPE_H

# include "ast.h"
# include "cmd_cache.h"
# include "parser_type.h"
# include <stddef.h>

// TODO: doc
typedef struct s_runner
{
	t_parser		parser;
	t_cmd_cache		*cmd_cache;		// borrowed
	size_t			loop_depth;
	size_t			control_depth;
	bool			errexit_ignored;
	struct s_runner	*parent;
	struct s_runner	*child;
	t_ast_root		ast_root;
}	t_runner;

#endif
