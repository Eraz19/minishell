/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_display.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:33:25 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/09 16:48:59 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_DISPLAY_H
# define PROMPT_DISPLAY_H

# include "libft_string.h"

typedef t_dstr	t_prompt_input;

t_prompt_input	display_prompt(t_dstr label);

#endif
