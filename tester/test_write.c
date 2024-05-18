/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:24:47 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/18 14:45:06 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_util.h"
#include "libasm.h"

static void	_copy(const char *path, int out, ssize_t (*write_func)())
{
	ssize_t		len;
	char		buf[1024];
	const int	in = open(path, O_RDONLY);

	bzero(buf, sizeof(buf));
	while (1)
	{
		errno = 0;
		len = read(in, buf, sizeof(buf));
		if (len <= 0)
			break ;
		write_func(out, buf, len);
	}
	close(in);
	if (len == 0)
		return ;
	dprintf(out, "rtn[%zd] errno[%d: %s]\n",
		len,
		errno,
		strerror(errno));
}

static void	_expect(int fd, void *data)
{
	_copy(data, fd, write);
}

static void	_output(int fd, void *data)
{
	_copy(data, fd, ft_write);
}

int	test_write(void)
{
	int	result;

	result = EXIT_SUCCESS;
	if (EXIT_FAILURE == run_test(_expect, _output, ""))
		result = EXIT_FAILURE;
	if (EXIT_FAILURE == run_test(_expect, _output, "."))
		result = EXIT_FAILURE;
	if (EXIT_FAILURE == run_test(_expect, _output, "Makefile"))
		result = EXIT_FAILURE;
	return (result);
}
