/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 02:07:56 by minjungk          #+#    #+#             */
/*   Updated: 2024/04/29 03:11:47 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// EXIT_SUCCESS, EXIT_FAILURE, mkstemp, system
#include <stdio.h>	// printf, dprintf, sprintf
#include <string.h>	// strlen, strcpy
#include <fcntl.h>	// open
#include <unistd.h>	// close, unlink
#include <assert.h>
#include "libasm.h"

static void	_usage(const char *pgname)
{
	printf("Usage: %s <filename>\n", pgname);
	printf("\thead -c 10000 /dev/urandom > filename\n");
}

static void	_test(const char *expect)
{
	ssize_t	len;
	int		fd[2];
	char	buf[1024];
	char	output[1024];
	char	command[1024];

	strcpy(output, "./output_XXXXXXXXXX");
	fd[0] = open(expect, O_RDONLY);
	fd[1] = mkstemp(output);
	assert(fd[0] != -1 && fd[1] != -1);
	len = read(fd[0], buf, sizeof(buf));
	while (len > 0)
	{
		write(fd[1], buf, len);
		write(STDOUT_FILENO, buf, len);
		len = read(fd[0], buf, sizeof(buf));
	}
	sprintf(command, "diff %s %s", expect, output);
	printf("\n");
	printf("diff ==========================================================\n");
	system(command);
	printf("===============================================================\n");
	close(fd[0]);
	close(fd[1]);
	unlink(output);
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		_usage(argv[0]);
		return (EXIT_FAILURE);
	}
	_test(argv[1]);
	return (EXIT_SUCCESS);
}
