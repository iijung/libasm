/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strcmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:00:54 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/18 14:27:31 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_util.h"
#include "libasm.h"

static void	_common(int (*func)(), int fd, const char *s1, const char *s2)
{
	int	i;

	{
		dprintf(fd, "echo $'");
		i = 0;
		while (s1[i])
			dprintf(fd, "\\x%02x", (unsigned char)s1[i++]);
		dprintf(fd, "'\n");
	}
	{
		dprintf(fd, "echo $'");
		i = 0;
		while (s2[i])
			dprintf(fd, "\\x%02x", (unsigned char)s2[i++]);
		dprintf(fd, "'\n");
	}
	dprintf(fd, "%d", func(s1, s2));
}

static void	_expect(int fd, void *data)
{
	const char	**s = data;

	_common(strcmp, fd, s[0], s[1]);
}

static void	_output(int fd, void *data)
{
	const char	**s = data;

	_common(ft_strcmp, fd, s[0], s[1]);
}

int	test_strcmp(void)
{
	int			i;
	int			result;
	const char	*testcase[][2] = {
	{"ABC", "ABC"}, {"ABC", "AB"}, {"ABA", "ABZ"}, {"ABJ", "ABC"},
	{"", ""}, {"42", ""}, {"", "42"},
	{"\201", "a"},
	{"\xff\xff", "\xff"},
	{"\xff\xff", "\xff\xfe"},
	{"\xff\xff", "\xff\xff"},
	{"\xff\xfe", "\xff\xff"},
	{"\xff", "\xff\xff"},
	{NULL, NULL}};

	result = EXIT_SUCCESS;
	i = 0;
	while (testcase[i][0] && testcase[i][1])
	{
		if (EXIT_FAILURE == run_test(_expect, _output, (void *)(testcase[i])))
			result = EXIT_FAILURE;
		++i;
	}
	return (result);
}
