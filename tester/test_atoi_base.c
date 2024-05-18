/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_atoi_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:46:12 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/18 18:46:23 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_util.h"
#include "libasm.h"

static void	_prefix(char *nptr, char *base, int same_val, int same_err)
{
	const char	*result[2] = {"❌", "✅"};

	printf("%s:%s (\"%20s\", \"%16s\") ",
		result[same_val],
		result[same_err],
		nptr,
		base);
}

static void	_decimal(char *nptr)
{
	int			org[2];
	int			you[2];

	enum e_type {val, err};
	errno = 0;
	you[val] = ft_atoi_base(nptr, "0123456789");
	you[err] = errno;
	errno = 0;
	org[val] = atoi(nptr);
	org[err] = errno;
	_prefix(nptr, NULL, you[val] == org[val], you[err] == org[err]);
	printf("= %11d (%d:%s)\n", you[val], you[err], strerror(you[err]));
}

static void	_custom(char *nptr, char *base, int expect, int errnum)
{
	int	diff;
	int	org[2];
	int	you[2];

	enum e_type {val, err};
	diff = (base == NULL);
	if (base == NULL)
		base = "0123456789";
	errno = 0;
	you[val] = ft_atoi_base(nptr, base);
	you[err] = errno;
	errno = 0;
	org[val] = atoi(nptr);
	org[err] = errno;
	_prefix(nptr, base, you[val] == expect, you[err] == errnum);
	printf("= %11d (%d:%s)\n", you[val], you[err], strerror(you[err]));
}

int	test_atoi_base(void)
{
	printf("\n");
	_decimal("123");
	_decimal("    123");
	_decimal("123abc");
	_custom("123abc", "55", 0, EINVAL);
	_decimal("");
	_decimal("0");
	_decimal("2147483647");
	_decimal("-2147483648");
	_custom("FF", "0123456789ABCDEF", 0xFF, 0);
	_custom("-FF", "0123456789ABCDEF", -0xFF, 0);
	_custom("7FFFFFFF", "0123456789ABCDEF", 0x7FFFFFFF, 0);
	_custom("-80000000", "0123456789ABCDEF", -0x80000000, 0);
	_custom("2147483648", NULL, INT_MAX, ERANGE);
	_custom("-2147483649", NULL, INT_MIN, ERANGE);
	_custom("4000000000", NULL, INT_MAX, ERANGE);
	_custom("9223372036854775807", NULL, INT_MAX, ERANGE);
	_custom("-9223372036854775808", NULL, INT_MIN, ERANGE);
	return (EXIT_SUCCESS);
}
