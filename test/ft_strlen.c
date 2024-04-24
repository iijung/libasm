/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:04:32 by minjungk          #+#    #+#             */
/*   Updated: 2024/04/24 22:22:06 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// EXIT_SUCCESS, EXIT_FAILURE
#include <stdio.h>	// printf
#include <string.h>	// strlen
#include "libasm.h"

static void	_usage(const char *pgname)
{
	int			i;
	const char	*example[] = {
		"''",
		"\"$(head -c 10000 /dev/urandom)\"",
		"\"$(tr -dc [:print:] < /dev/urandom | head -c 100000)\"",
		"\"$(tr -dc [:print:] < /dev/urandom | head -c 131071)\" # 0x1FFFF",
		NULL
	};

	printf("Usage: %s <str>\n", pgname);
	i = 0;
	while (example[i] != NULL)
		printf("\t%s %s\n", pgname, example[i++]);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		_usage(argv[0]);
		return (EXIT_FAILURE);
	}
	printf("strlen    = %zu\n", strlen(argv[1]));
	printf("ft_strlen = %zu\n", ft_strlen(argv[1]));
	return (EXIT_SUCCESS);
}
