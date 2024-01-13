/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:10:29 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/01/13 00:34:24 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int	count_stack(t_dll *start)
{
	t_dll	*ptr;
	int		i;

	if (!start)
		return (0);
	ptr = start -> lower;
	i = 1;
	while (ptr != start && ptr)
	{
		ptr = ptr -> lower;
		i++;
	}
	return (i);
}

void	del_list(t_dll *ref)
{
	t_dll	*ptr;
	int	count;

	count = count_stack(ref);
	while (count-- > 0)
	{
		ptr = ref -> lower;
		free(ref);
		ref = ptr;
	}
}

void	close_dll(t_dll *top)
{
	t_dll	*ptr;

	ptr = top;
	while (ptr -> lower)
		ptr = ptr -> lower;
	ptr -> lower = top;
	top -> higher = ptr;
}

int	get_offset(t_dll *a)
{
	int	len;
	int	temp;
	int	i;
	t_dll	*ptr;

	len = count_stack(a);
	i = 1;
	ptr = a;
	temp = a -> val;
	while (i++ < len)
	{
		temp = ptr -> val;
		ptr = ptr -> lower;
		if (temp >  ptr -> val)
			return (i);
	}
	return (i);
}		

int	get_steps(t_dll *stack, int x)
{
	int	len;

	len = count_stack(stack);
	if (x > len)
		return (0);
	if (len / 2 + 1 >= x)
		return (x - 1);
	else
		return (-(len + 1 - x));
}
