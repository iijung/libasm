/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:14:41 by minjungk          #+#    #+#             */
/*   Updated: 2024/05/09 17:03:46 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_H
# define LIBASM_H
# include <stddef.h>
# include <sys/types.h>

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

extern size_t	ft_strlen(const char *s);
extern char		*ft_strcpy(char *dest, const char *src);
extern char		*ft_strdup(const char *s);
extern int		ft_strcmp(const char *s1, const char *s2);
extern ssize_t	ft_write(int fd, const void *buf, size_t count);
extern ssize_t	ft_read(int fd, const void *buf, size_t count);

extern int		ft_atoi_base(char *str, char *base);
extern void		ft_list_push_front(t_list **begin_list, void *data);
extern int		ft_list_size(t_list *begin_list);
extern void		ft_list_sort(t_list **begin_list, int (*cmp)());

#endif /* LIBASM_H */
