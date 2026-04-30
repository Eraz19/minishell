/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _heredoc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 17:11:24 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/29 17:18:35 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HEREDOC_H
# define _HEREDOC_H

#include "scanner.h"

# define MAX_HEREDOCS 		16
# define HEREDOC_TMP_PATH	"/tmp/minishell_heredoc_"

t_file_path		create_heredoc_tmp_file(void);
bool			is_heredoc_expansion_enabled(t_token_value delimiter);

#endif
