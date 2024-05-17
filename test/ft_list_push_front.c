/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 07:38:00 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/17 14:16:02 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// EXIT_SUCCESS, atexit
#include <stdio.h>	// printf
#include "libasm.h"

static void	check_leaks(void)
{
	system("leaks ft_list_push_front");
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

static void	_free(t_list *curr)
{
	if (curr == NULL)
		return ;
	_free(curr->next);
	curr->next = NULL;
	free(curr);
}

static void	_show(t_list *curr)
{
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
	_free(head);
	return (EXIT_SUCCESS);
}
