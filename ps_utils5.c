/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:08:53 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/01/13 01:17:34 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

static void	fill_b(t_dll **a, t_dll **b)
{
	int	mv[3];
	fptr	func_ptr;
	int	i;
	int	j;

	if (count_stack(*a) >= 4)
		push_b(a, b);
	if (count_stack(*a) >= 4)
		push_b(a, b);
	while (count_stack(*a) > 3)
	{
		get_opt(a, b, mv);
		i = 0;
		while (i < 3)
		{
			func_ptr = get_fptr(mv[i], i);
			j = 0;
			while (j++ < ft_abs(mv[i]))
				func_ptr(a, b);
			i++;
		}
		push_b(a, b);
	}
}

static void	sort_three(t_dll **a, t_dll **b)
{
	int	ar[3];

	while (1)
	{
		ar[0] = (*a) -> val;
		ar[1] = (*a) -> lower -> val;
		ar[2] = (*a) -> higher -> val;
		if ((ar[1] > ar[2] && ar[2] > ar[0]) | (ar[2] > ar[0] && ar[0] > ar[1]))
			swap_a(*a);
		if ((ar[0] > ar[2] && ar[2] > ar[1]) | (ar[0] > ar[1] && ar[1] > ar[2]))
			rotate_a(a, b);
		if (ar[1] > ar[0] && ar[0] > ar[2])
			rev_rot_a(a, b);
		if (!(ar[0] > ar[1] && ar[1] > ar[2]))
			break;
	}
}

static void	final_rot(t_dll **a, t_dll **b)
{
	int		steps;
	fptr	func_ptr;

	steps = get_steps(*a, get_offset(*a));
	if (steps > 0)
		func_ptr = rotate_a;
	else
	{
		func_ptr = rev_rot_a;
		steps *= -1;
	}
	while (steps-- > 0)
		func_ptr(a, b);
}

static void	fill_a(t_dll **a, t_dll **b)
{
	int		steps;
	int		j;
	fptr	func_ptr;

	while (*b)
	{
		steps = get_steps(*a, get_pos_a(*a, get_val(*b, 1)));
		func_ptr = get_fptr(steps, 0);
		j = 0;
		while (j++ < ft_abs(steps))
			func_ptr(a, b);
		push_a(a, b);
	}
}

int	push_swap(t_dll **stack_a)
{
	t_dll	*stack_b;

	stack_b = 0;
	fill_b(stack_a, &stack_b);
	sort_three(stack_a, &stack_b);
	fill_a(stack_a, &stack_b);
	final_rot(stack_a, &stack_b);
	return (1);
}
