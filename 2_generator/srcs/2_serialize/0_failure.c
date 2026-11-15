/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_failure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:19:38 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:19:39 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>

bool	serializer_report_failure(void)
{
	return (perror("serializer"), false);
}
