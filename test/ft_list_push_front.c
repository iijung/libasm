/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 07:38:00 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/07 11:48:28 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// EXIT_SUCCESS, atexit
#include <stdio.h>	// printf
#include "libasm.h"

static void	check_leaks(void)
{
	system("leaks ft_list_push_front");
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

int	main(int ac, char **av)
{
	t_list	*head;

	atexit(check_leaks);
	head = NULL;
	printf("===============================================================\n");
	_show(head);
	ft_list_push_front(&head, "world");
	_show(head);
	ft_list_push_front(&head, "hello");
	_show(head);
	printf("===============================================================\n");
	_free(head);
	return (EXIT_SUCCESS);
}
