/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 17:20:58 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/09 17:37:59 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include <sys/stat.h>

typedef char	*t_file_path;

typedef union u_const_cast
{
	const char	*const_input;
	char		*input;
}	t_const_cast;

typedef struct stat	__stat_;

#endif
