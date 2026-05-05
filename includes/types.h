/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 17:20:58 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/04 21:43:07 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include <sys/stat.h>

typedef const char	*t_file_path;

typedef union u_const_cast
{
	const char	*const_input;
	char		*input;
}	t_const_cast;

typedef struct stat	__stat_;

#endif
