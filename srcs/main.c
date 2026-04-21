/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:17:30 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/21 18:08:48 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char *input = readline("minishell> ");
	if (input != NULL)
	{
		printf("You entered: %s\n", input);
		free(input);
	}
	return (0);
}

