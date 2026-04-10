/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_label.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 16:12:46 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/09 16:29:43 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_LABEL_H
# define PROMPT_LABEL_H

# include "libft_string.h"

typedef t_dstr	t_user_name;
typedef t_dstr	t_host_name;
typedef t_dstr	t_prompt_label;
typedef t_dstr	t_current_directory;

t_prompt_label	prompt_label(void);

#endif
