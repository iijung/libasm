/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 23:19:29 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/07 03:39:30 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// EXIT_SUCCESS, EXIT_FAILURE
#include <stdio.h>	// printf
#include <string.h>	// strerror
#include <errno.h>
#include "libasm.h"

static void	_test(char *nptr, char *base, const int expect)
{
	const char	*result[2] = {"❌", "✅"};
	int			output;

	errno = 0;
	output = ft_atoi_base(nptr, base);
	printf("%s ft_atoi_base(\"%20s\", \"%16s\") = %11d (%s)\n",
		result[output == expect],
		nptr,
		base,
		output,
		strerror(errno));
}

static void	_default(void)
{
	printf("\n[default test]\n");
	_test("123", "0123456789", atoi("123"));
	_test("    123", "0123456789", atoi("    123"));
	_test("123abc", "0123456789", atoi("123abc"));
	_test("123abc", "55", 0);
	_test("", "0123456789", 0);
	printf("\n[INT_MIN ~ INT_MAX]\n");
	_test("0", "0123456789", atoi("0"));
	_test("2147483647", "0123456789", atoi("2147483647"));
	_test("-2147483648", "0123456789", atoi("-2147483648"));
	_test("2147483648", "0123456789", atoi("2147483647"));
	_test("-2147483649", "0123456789", atoi("-2147483648"));
	_test("FF", "0123456789ABCDEF", 0xFF);
	_test("-FF", "0123456789ABCDEF", -0xFF);
	_test("7FFFFFFF", "0123456789ABCDEF", 0x7FFFFFFF);
	_test("-80000000", "0123456789ABCDEF", -0x80000000);
	printf("\n[LONG_MIN ~ LONG_MAX (should fail)]\n");
	_test("4000000000", "0123456789", atoi("4000000000"));
	_test("9223372036854775807", "0123456789", atoi("9223372036854775807"));
	_test("-9223372036854775808", "0123456789", atoi("-9223372036854775808"));
}

int	main(int ac, char **av)
{
	int		output;
	char	*base;

	if (ac < 2)
	{
		printf("Usage: %s <str> [base]\n", av[0]);
		_default();
		return (EXIT_FAILURE);
	}
	base = "0123456789";
	if (ac != 2)
		base = av[2];
	errno = 0;
	output = ft_atoi_base(av[1], base);
	printf("ft_atoi_base(\"%s\", \"%s\") = %d (%s)\n",
		av[1],
		base,
		output,
		strerror(errno));
	return (EXIT_SUCCESS);
}
