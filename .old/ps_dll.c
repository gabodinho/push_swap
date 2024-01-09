/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_dll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 01:01:18 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/12/06 20:56:08 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
//#include <unistd.h>
#include <ctype.h>


typedef struct	s_dll
{
	int				val;
	struct s_dll	*prev;
	struct s_dll	*next;
} t_dll;

t_dll	*new_node(int val)
{
	t_dll	*new;

	new = malloc(sizeof(t_dll));
	if (!new)
		return (NULL);
	new -> val = val;
	new -> next = 0;
	new -> prev = 0;
	return (new);
}

void	del_list(t_dll *ref)
{
	if (ref -> next)
		del_list(ref -> next);
	free(ref);
	ref = 0;
}

void	add_last(t_dll **ref, int val)
{
	t_dll	*ptr;
	t_dll	*new;

	ptr = *ref;
	new = new_node(val);
	if (!ptr)
	{
		*ref = new;
		return ;
	}
	while (ptr -> next)
		ptr = ptr -> next;
	if (!new)
		del_list(*ref);
	ptr -> next = new;
	new -> prev = ptr;
}

void	printl(t_dll *start)
{
	t_dll	*ptr;

	ptr = start;
	while (ptr)
	{
		printf("val: %d\n", ptr -> val);
		ptr = ptr -> next;
	}
}

int	main(int argc, char *argv[])
{
	t_dll	*start;
	t_dll	*ptr;

	start = 0;
//	start = new_node(10);
	add_last(&start, 20);
	add_last(&start, 30);
	ptr = start;
	printl(start);
	del_list(start);
	printl(start);
	return (0);
}
