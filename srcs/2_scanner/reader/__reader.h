/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __reader.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:37:09 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 20:36:44 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __READER_H
# define __READER_H

#include "error.h"
#include "types.h"

t_error	reader_heredoc(char **res);
t_error	reader_new_input(char **res);
t_error	reader_continuation(char **res);
t_error	reader_file_input(char **res, t_file_path path);

t_error	readline_(char **res, const char *prompt);

#endif
