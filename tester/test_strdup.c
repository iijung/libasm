/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:16:23 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/18 18:28:04 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_util.h"
#include "libasm.h"

static void	_expect(int fd, void *data)
{
	const char	*s = data;

	dprintf(fd, "%s", s);
}

static void	_output(int fd, void *data)
{
	char		*rtn;

	rtn = ft_strdup(data);
	dprintf(fd, "%s", rtn);
	free(rtn);
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

int	test_strdup(void)
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
