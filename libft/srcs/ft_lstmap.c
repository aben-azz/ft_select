/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 10:51:57 by midrissi          #+#    #+#             */
/*   Updated: 2018/10/13 12:55:59 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*temp;
	t_list	*begining;

	begining = (t_list *)malloc(sizeof(t_list));
	if (!begining || !lst || !f || !*f)
		return (NULL);
	begining = f(lst);
	lst = lst->next;
	temp = begining;
	while (lst)
	{
		temp->next = f(lst);
		temp = temp->next;
		lst = lst->next;
	}
	temp->next = NULL;
	return (begining);
}
