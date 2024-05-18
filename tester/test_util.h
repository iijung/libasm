/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_util.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:33:23 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/18 18:28:12 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_UTIL_H
# define TEST_UTIL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <limits.h>

typedef struct s_tester
{
	char	*symbol;
	int		(*func)(void);
}	t_tester;

typedef struct s_case_atoi_base
{
	char	*nptr;
	char	*base;
	int		expect;
	int		errnum;
}	t_case_atoi_base;

typedef void	(*t_test)(int, void *);

extern char	*random_str(size_t len, int min, int max);
extern int	all_test(const char *title, const t_tester *tester);
extern int	run_test(t_test expect_func, t_test output_func, void *data);

#endif /* TEST_UTIL_H */
