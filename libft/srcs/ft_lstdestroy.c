/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdestroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 06:29:17 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/09 06:43:04 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstdestroy(t_list **lst)
{
	t_list *save;

	while (*lst)
	{
		save = *lst;
		*lst = (*lst)->next;
		ft_memdel(&(save->content));
		ft_memdel((void **)&save);
	}
	*lst = NULL;
	return (0);
}
