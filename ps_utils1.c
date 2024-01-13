/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:16:53 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/01/12 22:16:54 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

static int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

static void	fill_zeros(int *ar)
{
	int	i;

	i = 0;
	while (i < 3)
		ar[i++] = 0;
}

static int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

// mv = [ra || rra, rb || rrb, rr || rrr]
void	get_moves(int na, int nb, int mv[3])
{
	int	temp;

	fill_zeros(mv);
	if (na > 0 && nb > 0)
	{
		mv[2] = ft_min(na, nb);
		temp = na;
		na -= ft_min(na, nb);
		nb -= ft_min(temp, nb);
	}
	else if (na < 0 && nb < 0)
	{
		mv[2] = ft_max(na, nb);
		temp = na;
		na -= ft_max(na, nb);
		nb -= ft_max(temp, nb);
	}
	mv[0] = na;
	mv[1] = nb;
}

int	get_nmoves(int a, int b)
{
	if (a * b > 0)
		return (ft_max(ft_abs(a), (ft_abs(b))));
	else if (a * b < 0)
		return (ft_abs(a - b));
	else if (a == 0 && b == 0)
		return (0);
	else
		return (ft_max(ft_abs(a), (ft_abs(b))));
}
