/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils9.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 01:01:18 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/01/10 18:18:59 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int	ft_abs(int i)
{
	if (i < 0)
		return (i * -1);
	else
		return (i);
}

void	swap_a(t_dll *topa)
{
	int	temp;

	if (count_stack(topa) < 2)
		return ;
	temp = topa -> val;
	topa -> val = (topa -> lower) -> val;
	(topa -> lower) -> val = temp;
	ft_printf("sa\n");
}

void	rotate_a(t_dll **a, t_dll **b)
{
	(void)	b;
	if (!*a)
		return ;
	*a = (*a) -> lower;
	ft_printf("ra\n");
}

void	rotate_b(t_dll **a, t_dll **b)
{
	(void)	a;
	if (!*b)
		return ;
	*b = (*b) -> lower;
	ft_printf("rb\n");
}
