/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 02:07:56 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/17 10:17:16 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// EXIT_SUCCESS, EXIT_FAILURE, mkstemp, system
#include <stdio.h>	// printf, dprintf, snprintf
#include <string.h>	// strlen, strcpy
#include <fcntl.h>	// open
#include <unistd.h>	// close, read, write, unlink
#include <limits.h>	// PATH_MAX
#include <assert.h>
#include <errno.h>
#include "libasm.h"

static void	_usage(const char *pgname)
{
	printf("Usage: %s <filename>\n", pgname);
	printf("\thead -c 10000 /dev/urandom > filename\n");
}

static void	_copy(const char *filename, int out, ssize_t (*read_func)())
{
	ssize_t		len;
	char		buf[1024];
	const int	in = open(filename, O_RDONLY);

	bzero(buf, sizeof(buf));
	while (1)
	{
		errno = 0;
		len = read_func(in, buf, sizeof(buf));
		if (len <= 0)
			break ;
		write(out, buf, len);
		write(STDOUT_FILENO, buf, len);
	}
	close(in);
	if (len == 0)
		return ;
	dprintf(out, "rtn[%zd] errno[%d: %s] buf[%s]\n",
		len,
		errno,
		strerror(errno),
		buf);
}

static int	_test(const char *filename)
{
	int			fd[2];
	char		name[2][PATH_MAX];
	char		cmd[PATH_MAX * 2 + 16];
	int			result;

	enum e_type {expect, output};
	strcpy(name[expect], "./expect_XXXXXXXXXX");
	strcpy(name[output], "./output_XXXXXXXXXX");
	fd[expect] = mkstemp(name[expect]);
	fd[output] = mkstemp(name[output]);
	_copy(filename, fd[expect], read);
	_copy(filename, fd[output], ft_read);
	close(fd[expect]);
	close(fd[output]);
	printf("output ========================================================\n");
	snprintf(cmd, sizeof(cmd), "cat %s", name[output]);
	system(cmd);
	printf("\n");
	printf("diff ==========================================================\n");
	snprintf(cmd, sizeof(cmd), "diff %s %s", name[expect], name[output]);
	result = system(cmd);
	printf("===============================================================\n");
	unlink(name[expect]);
	unlink(name[output]);
	return (result);
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
