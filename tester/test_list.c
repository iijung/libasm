/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:07:12 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/18 18:45:46 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include "test_util.h"

static void	_show(t_list *curr)
{
	printf("size[%5d]\t| ", ft_list_size(curr));
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

static void	_create(t_list **head, int size)
{
	char	*data;

	printf("# create\n");
	while (size-- > 0)
	{
		data = random_str(2, '0', '9');
		ft_list_push_front(head, data);
		printf("mk[%s] => ", data);
		_show(*head);
	}
}

static void	_destroy(t_list **head)
{
	char	*data;

	printf("# remove\n");
	while (*head)
	{
		data = strdup((*head)->data);
		ft_list_remove_if(head, data, _cmp, free);
		printf("rm[%s] => ", data);
		free(data);
		_show(*head);
	}
}

int	test_list(void)
{
	t_list	*head;

	head = NULL;
	printf("\n");
	_create(&head, 20);
	printf("# sort\n");
	ft_list_sort(&head, _cmp);
	_show(head);
	_destroy(&head);
	return (EXIT_SUCCESS);
}
