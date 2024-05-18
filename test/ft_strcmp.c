/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 03:35:54 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/18 13:05:25 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// EXIT_SUCCESS, EXIT_FAILURE
#include <stdio.h>	// printf
#include <string.h>	// strlen, strcmp
#include "libasm.h"

static void	_test(const char *s1, const char *s2)
{
	printf("expect[%8d] result[%8d]\n", strcmp(s1, s2), ft_strcmp(s1, s2));
}

static void	_default(void)
{
	printf("[default test]=================================================\n");
	_test("ABC", "ABC");
	_test("ABC", "AB");
	_test("ABA", "ABZ");
	_test("ABJ", "ABC");
	_test("\201", "A");
	printf("[custom test]==================================================\n");
	_test("\xff", "");
	_test("\xff", "\xfe");
	_test("\xff", "\xff");
	_test("\xfe", "\xff");
	_test("", "\xff");
	printf("===============================================================\n");
}

int	main(int argc, char **argv)
{
	char	*s1;
	char	*s2;

	if (argc != 3)
	{
		printf("Usage: %s <str1> <str2>\n", argv[0]);
		_default();
		printf("Run, ");
		printf("s=\"$(tr -dc [:print:] < /dev/urandom | head -c 131071)\";");
		printf("./ft_strcmp \"$s\" \"$s\"\n");
		printf("Run, ./ft_strcmp $'\\xff' $'\\xfe'\n");
		return (EXIT_FAILURE);
	}
	s1 = argv[1];
	s2 = argv[2];
	printf("===============================================================\n");
	printf("expect[%8d] result[%8d]\n", strcmp(s1, s2), ft_strcmp(s1, s2));
	printf("===============================================================\n");
	return (EXIT_SUCCESS);
}
