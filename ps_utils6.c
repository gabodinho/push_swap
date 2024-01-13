/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_funcs6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:09:43 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/01/12 23:09:46 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

// given that b is sorted (desc), this func returns the postition of x in b
static int	get_pos_b(t_dll *b, int x)
{
	int		pos;
	int		v;
	int		h;
	t_dll	*ptr;

	if (!b)
		return (0);	// --> create new node and put on top
	else if (count_stack(b) == 1)
		return (1);
	ptr = b;
	pos = 1;
	v = ptr -> val;
	h = (ptr -> higher) -> val;
	while ((v > x && x > h) || (h > v && v > x) || (x > h && h > v))
	{
		pos++;
		h = v;
		ptr = ptr -> lower;
		v = ptr -> val;
	}
	return (pos);
}

int	get_pos_a(t_dll *b, int x)
{
	int		pos;
	int		v;
	int		h;
	t_dll	*ptr;

	if (!b)
		return (0);	// --> create new node and put on top
	else if (count_stack(b) == 1)
		return (1);
	ptr = b;
	pos = 1;
	v = ptr -> val;
	h = (ptr -> higher) -> val;
	while ((v < x && x < h) || (h < v && v < x) || (x < h && h < v))
	{
		pos++;
		h = v;
		ptr = ptr -> lower;
		v = ptr -> val;
	}
	return (pos);
}

int	get_val(t_dll *stack, int idx)
{
	int	i;

	i = 1;
	while (i++ < idx)
		stack = stack -> lower;
	return (stack -> val);
}

void	get_opt(t_dll **a, t_dll **b, int mv[3])
{
	int	ar[6];
	int	len;
	int	i;

	len = count_stack(*a);
	i = 1;
	ar[3] = 0;
	while (i <= len)
	{
		ar[0] = i;
		ar[1] = get_steps(*a, i);
		ar[2] = get_steps(*b, get_pos_b(*b, get_val(*a, i++)));
		if (ar[3] == 0 || get_nmoves(ar[1], ar[2]) < get_nmoves(ar[4], ar[5]))
		{
			ar[3] = ar[0];
			ar[4] = ar[1];
			ar[5] = ar[2];
		}
	}
	get_moves(ar[4], ar[5], mv);
}

fptr get_fptr(int mv, int i)
{
	if (i == 0)
	{
		if (mv > 0)
			return (rotate_a);
		else
			return (rev_rot_a);
	}
	else if (i == 1)
	{
		if (mv > 0)
			return (rotate_b);
		else
			return (rev_rot_b);
	}
	else
	{
		if (mv > 0)
			return (rotate_ab);
		else
			return (rev_rot_ab);
	}
}
