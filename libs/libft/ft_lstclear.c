/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 04:07:51 by rkedida           #+#    #+#             */
/*   Updated: 2022/04/04 04:08:12 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*clr;

	if (!del || !lst)
		return ;
	while (*lst)
	{
		clr = *lst;
		*lst = (*lst)->next;
		del(clr->content);
		free(clr);
	}
}
