/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _reader.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 16:30:26 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/11 17:32:04 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _READER_H
# define _READER_H

# include <stdbool.h>
# include "types.h"

char	*read_tty(void);
bool	complete_tty(char **prev_line);

char	*read_script(t_file_path script);

#endif
