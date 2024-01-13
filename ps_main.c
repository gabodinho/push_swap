/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:11:22 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/01/13 01:04:30 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

int	main(int argc, char *argv[])
{
	int	len;
	t_dll	*top[1];

	*top = check_input(argc, argv);
	close_dll(*top);
	len = count_stack(*top);
	if (len == 2)
	{
		if ((*top) -> val > ((*top) -> lower) -> val)
			swap_a(*top);
	}
	else if (len > 2)
		push_swap(top);
	del_list(*top);
	return (0);
}
