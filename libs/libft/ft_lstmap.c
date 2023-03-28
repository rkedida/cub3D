/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 04:09:32 by rkedida           #+#    #+#             */
/*   Updated: 2022/04/04 04:10:01 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newnode;
	t_list	*orig;
	t_list	*newlist;

	newlist = NULL;
	orig = lst;
	while (orig)
	{
		newnode = ft_lstnew(f(orig->content));
		if (newnode)
			ft_lstadd_back(&newlist, newnode);
		else
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		orig = orig->next;
	}
	return (newlist);
}
