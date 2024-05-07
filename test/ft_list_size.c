/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:06:38 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/07 11:49:51 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// EXIT_SUCCESS, atexit
#include <stdio.h>	// printf
#include "libasm.h"

static void	check_leaks(void)
{
	system("leaks ft_list_size");
}

static void	_usage(const char *pgname)
{
	int			i;
	const char	*example[] = {
		"seq 100",
		"jot -r 10 1 100",
		NULL
	};

	printf("Usage: %s [num1, ...]\n", pgname);
	i = 0;
	while (example[i] != NULL)
		printf("\t%s $(%s)\n", pgname, example[i++]);
}

static void	_show(t_list *curr)
{
	printf("size[%d]\t", ft_list_size(curr));
	while (curr)
	{
		printf("[%s] -> ", (char *)curr->data);
		curr = curr->next;
	}
	printf("(null)\n");
}

int	main(int argc, char **argv)
{
	t_list	*head;
	t_list	*tmp;

	if (argc < 2)
	{
		_usage(argv[0]);
		return (EXIT_FAILURE);
	}
	atexit(check_leaks);
	head = NULL;
	while (--argc > 0)
		ft_list_push_front(&head, argv[argc]);
	printf("===============================================================\n");
	_show(head);
	printf("===============================================================\n");
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	return (EXIT_SUCCESS);
}
