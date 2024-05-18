/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:08:09 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/18 18:45:58 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libasm.h"
#include "test_util.h"

extern int	test_strlen(void);
extern int	test_strcpy(void);
extern int	test_strcmp(void);
extern int	test_strdup(void);
extern int	test_write(void);
extern int	test_read(void);
extern int	test_atoi_base(void);
extern int	test_list(void);

static const t_tester	g_mandatory[] = {
{"ft_strlen", test_strlen},
{"ft_strcpy", test_strcpy},
{"ft_strcmp", test_strcmp},
{"ft_strdup", test_strdup},
{"ft_write", test_write},
{"ft_read", test_read},
{NULL, NULL}
};
static const t_tester	g_bonus[] = {
{"ft_atoi_base", test_atoi_base},
{"ft_list", test_list},
{NULL, NULL}
};

static void	check_leaks(void)
{
	char	command[256];

	snprintf(command, sizeof(command), "leaks %d", getpid());
	system(command);
}

static int	_usage(const char *pgname, int result)
{
	printf("Usage: %s [OPTIONS]\n", pgname);
	printf("\n"
		"OPTIONS:\n"
		" -h\thelp\n"
		" -m\tmandatory\n"
		" -b\tbonus\n");
	return (result);
}

static int	_test(char mandatory, char bonus)
{
	int	result;

	if (0 == mandatory && 0 == bonus)
	{
		mandatory = 1;
		bonus = 1;
	}
	result = EXIT_SUCCESS;
	if (mandatory && EXIT_FAILURE == all_test("mandatory", g_mandatory))
		result = EXIT_FAILURE;
	if (bonus && EXIT_FAILURE == all_test("bonus", g_bonus))
		result = EXIT_FAILURE;
	return (result);
}

int	main(int argc, char **argv)
{
	int		ch;
	char	flag[2];

	enum e_flag {mandatory, bonus};
	bzero(flag, sizeof(flag));
	while (1)
	{
		ch = getopt(argc, argv, "mbh");
		if (-1 == ch)
			break ;
		else if (ch == 'h')
			return (_usage(argv[0], EXIT_SUCCESS));
		else if (ch == 'm')
			flag[mandatory] = 1;
		else if (ch == 'b')
			flag[bonus] = 1;
		else
			return (_usage(argv[0], EXIT_FAILURE));
	}
	atexit(check_leaks);
	return (_test(flag[mandatory], flag[bonus]));
}
