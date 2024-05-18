/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 11:48:08 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/18 18:28:01 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_util.h"
#include "libasm.h"

static void	_common(int fd, int same_address, const char *str)
{
	dprintf(fd, "%d %s", same_address, str);
}

static void	_expect(int fd, void *data)
{
	_common(fd, 1, data);
}

static void	_output(int fd, void *data)
{
	const char		*src = data;
	const size_t	len = strlen(src);
	char			*dst;
	char			*rtn;

	dst = malloc(len + 1);
	if (dst == NULL)
		dprintf(fd, "%s", strerror(errno));
	else
	{
		rtn = ft_strcpy(dst, src);
		_common(fd, rtn == dst, dst);
		free(dst);
	}
}

static int	_big(size_t len)
{
	int		result;
	char	*s;

	result = 0;
	s = random_str(len, ' ', '~');
	if (s == NULL)
		return (EXIT_SUCCESS);
	result = run_test(_expect, _output, (void *)s);
	free(s);
	return (result);
}

int	test_strcpy(void)
{
	int	result;

	result = EXIT_SUCCESS;
	if (EXIT_FAILURE == run_test(_expect, _output, ""))
		result = EXIT_FAILURE;
	if (EXIT_FAILURE == run_test(_expect, _output, "hello"))
		result = EXIT_FAILURE;
	if (EXIT_FAILURE == run_test(_expect, _output, "hello wolrd!"))
		result = EXIT_FAILURE;
	if (EXIT_FAILURE == _big(100))
		result = EXIT_FAILURE;
	if (EXIT_FAILURE == _big(1000))
		result = EXIT_FAILURE;
	if (EXIT_FAILURE == _big(10000))
		result = EXIT_FAILURE;
	if (EXIT_FAILURE == _big(100000))
		result = EXIT_FAILURE;
	if (EXIT_FAILURE == _big(1000000))
		result = EXIT_FAILURE;
	if (EXIT_FAILURE == _big(10000000))
		result = EXIT_FAILURE;
	return (result);
}
