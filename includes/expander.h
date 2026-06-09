/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:32:43 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 11:19:21 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "error.h"
# include "_quote_remove.h"

t_error	expander_quote_remove(t_buff *res, t_buff *input);

#endif
