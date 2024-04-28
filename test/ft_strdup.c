/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:39:48 by minjungk          #+#    #+#             */
/*   Updated: 2024/04/28 21:50:04 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// EXIT_SUCCESS, EXIT_FAILURE
#include <stdio.h>	// printf
#include <string.h>	// strlen, strcmp
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
	char	*rtn;

	if (argc != 2)
	{
		_usage(argv[0]);
		return (EXIT_FAILURE);
	}
	rtn = ft_strdup(argv[1]);
	printf("===============================================================\n");
	printf("%s\n", rtn);
	printf("===============================================================\n");
	if (0 == strcmp(argv[1], rtn))
		printf("same\n");
	else
		printf("diff\n");
	free(rtn);
	return (EXIT_SUCCESS);
}
