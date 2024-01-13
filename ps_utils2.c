/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:05:44 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/01/12 23:05:49 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

static void	rm_top_node(t_dll **top)
{
	t_dll	*temp;

	if (!*top)
		return ;
	else if (count_stack(*top) == 1)
	{
		del_list(*top);
		*top = NULL;
	}
	else
	{
		(*top) -> lower -> higher = (*top) -> higher;
		(*top) -> higher -> lower = (*top) -> lower;
		temp = (*top) -> lower;
		free(*top);
		*top = temp;
	}
}

static void	add_top_node(t_dll **top, t_dll *node)
{
	t_dll	*temp;

	if (*top)
	{
		temp = *top;
		node -> higher = temp -> higher;
		(temp -> higher) -> lower = node;
		temp -> higher = node;
		node -> lower = temp;
		*top = node;
	}
	else
	{
		*top = node;
		close_dll(*top);
	}
}

t_dll	*new_node(int val)
{
	t_dll	*new;

	new = malloc(sizeof(t_dll));
	if (!new)
		return (NULL);
	new -> val = val;
	new -> lower = 0;
	new -> higher = 0;
	return (new);
}

void	push_a(t_dll **a, t_dll **b)
{
	if (!*b)
		return ;
	add_top_node(a, new_node((*b) -> val));
	rm_top_node(b);
	ft_printf("pa\n");
}

void	push_b(t_dll **a, t_dll **b)
{
	if (!*a)
		return ;
	add_top_node(b, new_node((*a) -> val));
	rm_top_node(a);
	ft_printf("pb\n");
}
