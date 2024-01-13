/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 01:01:18 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/01/12 23:14:57 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

void	rotate_ab(t_dll **a, t_dll **b)
{
	if (*a)
		*a = (*a) -> lower;
	if (*b)
		*b = (*b) -> lower;
	ft_printf("rr\n");
}

void	rev_rot_a(t_dll **a, t_dll **b)
{
	(void)	b;
	if (!*a)
		return ;
	*a = (*a) -> higher;
	ft_printf("rra\n");
}

void	rev_rot_b(t_dll **a, t_dll **b)
{	
	(void)	a;
	if (!*b)
		return ;
	*b = (*b) -> higher;
	ft_printf("rrb\n");
}

void    rev_rot_ab(t_dll **a, t_dll **b)
{
	if (*a)
		*a = (*a) -> higher;
	if (*b)
		*b = (*b) -> higher;
	ft_printf("rrr\n");
}
