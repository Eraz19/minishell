/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:17:30 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/09 17:09:04 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "prompt.h"

int	main(void)
{
	t_prompt_input	input;

	while (TRUE)
	{
		input = add_to_history(display_prompt(prompt_label()));
		if (input.s != NULL)
		{
			printf("You entered: %s\n", input.s);
			free(input.s);
		}
	}
	return (0);
}
