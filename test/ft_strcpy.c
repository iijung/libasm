/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 23:52:51 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/10 16:17:07 by minjungk         ###   ########.fr       */
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
	char		*rtn;
	char		*src;
	char		*dest;
	const char	*result[2] = {"❌", "✅"};

	if (argc != 2)
	{
		_usage(argv[0]);
		return (EXIT_FAILURE);
	}
	src = argv[1];
	dest = calloc(sizeof(char), strlen(src) + 1);
	rtn = ft_strcpy(dest, src);
	printf("===============================================================\n");
	printf("%s\n", rtn);
	printf("===============================================================\n");
	printf("%s address\n", result[rtn == dest]);
	printf("%s strcmp(src, dst)\n", result[0 == strcmp(src, dest)]);
	free(dest);
	return (EXIT_SUCCESS);
}
