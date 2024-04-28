/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:46:32 by minjungk          #+#    #+#             */
/*   Updated: 2024/04/29 03:12:04 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// EXIT_SUCCESS, EXIT_FAILURE, mkstemp, system
#include <stdio.h>	// printf, dprintf, sprintf
#include <string.h>	// strlen, strcpy
#include <unistd.h>	// close, unlink
#include <assert.h>
#include <errno.h>
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

static void	_test(const char *str)
{
	int				fd[2];
	char			tmp[2][1024];
	char			command[1024];
	const size_t	len = strlen(str);

	strcpy(tmp[0], "./expect_XXXXXXXXXX");
	strcpy(tmp[1], "./output_XXXXXXXXXX");
	fd[0] = mkstemp(tmp[0]);
	fd[1] = mkstemp(tmp[1]);
	assert(fd[0] != -1 && fd[1] != -1);
	errno = 0;
	dprintf(fd[0], "\nret[%zd] errno[%d]\n", write(fd[0], str, len), errno);
	errno = 0;
	dprintf(fd[1], "\nret[%zd] errno[%d]\n", ft_write(fd[1], str, len), errno);
	close(fd[0]);
	close(fd[1]);
	sprintf(command, "diff %s %s", tmp[0], tmp[1]);
	printf("diff ==========================================================\n");
	system(command);
	printf("===============================================================\n");
	unlink(tmp[0]);
	unlink(tmp[1]);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		_usage(argv[0]);
		return (EXIT_FAILURE);
	}
	_test(argv[1]);
	return (EXIT_SUCCESS);
}
