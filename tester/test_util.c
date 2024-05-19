/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:36:34 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/18 18:29:04 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_util.h"
#include <time.h>
#include <unistd.h>
#include <string.h>

char	*random_str(size_t len, int min, int max)
{
	size_t		i;
	char		*s;
	static int	seed = 42;

	s = malloc(len + 1);
	if (s == NULL)
		return (NULL);
	seed += time(NULL);
	srand(seed);
	i = 0;
	while (i < len)
	{
		s[i] = (rand() % (max - min + 1)) + min;
		++i;
	}
	s[len] = '\0';
	return (s);
}

int	all_test(const char *title, const t_tester *tester)
{
	int	i;
	int	result;

	result = EXIT_SUCCESS;
	printf("===============================================================\n");
	printf("%s\n", title);
	printf("===============================================================\n");
	i = 0;
	while (tester && tester[i].symbol)
	{
		printf("%-20s: ", tester[i].symbol);
		if (EXIT_FAILURE == tester[i].func())
			result = EXIT_FAILURE;
		printf("\n");
		++i;
	}
	return (result);
}

int	diff_file(const char *expect, const char *output)
{
	char	cmd[PATH_MAX * 3];

	snprintf(cmd, sizeof(cmd), "diff -u %s %s > /dev/null", expect, output);
	if (EXIT_SUCCESS == system(cmd))
		return (EXIT_SUCCESS);
	snprintf(cmd, sizeof(cmd), "diff -u %s %s >> trace.out", expect, output);
	system(cmd);
	return (EXIT_FAILURE);
}

int	run_test(t_test expect_func, t_test output_func, void *data)
{
	int			fd[2];
	char		name[2][PATH_MAX];
	int			result;
	const char	*is_success[2] = {"❌", "✅"};

	enum e_type {expect, output};
	strcpy(name[expect], "./expect_XXXXXXXXXX");
	strcpy(name[output], "./output_XXXXXXXXXX");
	fd[expect] = mkstemp(name[expect]);
	fd[output] = mkstemp(name[output]);
	{
		expect_func(fd[expect], data);
		output_func(fd[output], data);
	}
	close(fd[expect]);
	close(fd[output]);
	result = diff_file(name[expect], name[output]);
	unlink(name[expect]);
	unlink(name[output]);
	printf("%s", is_success[EXIT_SUCCESS == result]);
	return (result);
}
