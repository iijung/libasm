/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:12:02 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/10 14:20:32 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// EXIT_SUCCESS, atexit
#include <stdio.h>	// printf
#include "libasm.h"

static void	check_leaks(void)
{
	system("leaks ft_list_remove_if");
}

static void	_usage(const char *pgname)
{
	int			i;
	const char	*example[] = {
		"seq 10 | shuf | xargs ",
		"seq 10 | sort -R | xargs ",
		"jot -r 10 1 100 | sort -uR | xargs",
		NULL
	};

	printf("Usage: %s [num1, ...]\n", pgname);
	i = 0;
	while (example[i] != NULL)
		printf("\t%s %s\n", example[i++], pgname);
}

static void	_show(t_list *curr)
{
	printf("size[%5d]\t", ft_list_size(curr));
	while (curr)
	{
		printf("[%s] -> ", (char *)curr->data);
		curr = curr->next;
	}
	printf("(null)\n");
}

static int	_cmp(char *a, char *b)
{
	const int	num1 = atoi(a);
	const int	num2 = atoi(b);

	return (num1 - num2);
}

int	main(int argc, char **argv)
{
	int		i;
	t_list	*head;

	if (argc < 2)
	{
		_usage(argv[0]);
		return (EXIT_FAILURE);
	}
	atexit(check_leaks);
	head = NULL;
	i = argc;
	while (--i > 0)
		ft_list_push_front(&head, argv[i]);
	_show(head);
	printf("===============================================================\n");
	ft_list_sort(&head, _cmp);
	_show(head);
	while (++i < argc)
	{
		ft_list_remove_if(&head, argv[i], _cmp, NULL);
		_show(head);
	}
	printf("===============================================================\n");
	_show(head);
	return (EXIT_SUCCESS);
}
