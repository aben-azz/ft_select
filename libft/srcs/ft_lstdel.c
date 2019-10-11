/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 10:27:35 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/09 06:44:41 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del) (void *, size_t))
{
	t_list *list;

	list = *alst;
	while (list)
	{
		*alst = list->next;
		ft_lstdelone(&list, del);
		list = *alst;
	}
	*alst = NULL;
}
