/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 01:01:18 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/12/20 19:06:07 by ggiertzu         ###   ########.fr       */
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
	struct s_dll	*higher;
	struct s_dll	*lower;
} t_dll;

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

int	count_dll(t_dll	*top)
{
	t_dll	*ptr;
	int		i;

	ptr = top;
	i = 0;
	while (ptr)
	{
		i++;
		ptr = ptr -> lower;
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
	while (ptr -> lower)
		ptr = ptr -> lower;
	if (!new)
		del_list(*ref);
	ptr -> lower = new;
	new -> higher = ptr;
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

void	throw_error(int val)
{
	if (val == EXIT_FAILURE)
	{
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
}

void	free_list(t_dll *top)
{
	del_list(top);
	throw_error(EXIT_FAILURE);
}



// delete this function for final version
void	printl(t_dll *top)
{
	t_dll	*ptr;

	ptr = top;
	while (ptr)
	{
		printf("val: %d\n", ptr -> val);
		ptr = ptr -> lower;
	}
}

void	print_stacks(t_dll *a, t_dll *b)
{
	int	x = count_stack(a);
	int	y = count_stack(b);
	t_dll *ptr_a = a;
	t_dll *ptr_b = b;

	printf(" A\tB\n");
	while (x > 0  || y > 0)
	{
		if (x-- > 0)
		{
			printf("%d\t", ptr_a -> val);
			ptr_a = ptr_a -> lower;
		}
		else
			printf(" \t");
		if (y-- > 0)
		{
			printf("%d\n", ptr_b -> val);
			ptr_b = ptr_b -> lower;
		}
		else
			printf("\n");
	}
}


void	rm_top_node(t_dll **top)
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

void	add_top_node(t_dll **top, t_dll *node)
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

/*
t_dll	*cp_node(t_dll *node)
{
	int	temp;

	if (!node)
		return ;
	temp = node -> val;
	return (new_node(
*/

void	swap_a(t_dll *topa)
{
	int	temp;

	if (count_dll(topa) < 2)
		return ;
	temp = topa -> val;
	topa -> val = (topa -> lower) -> val;
	(topa -> lower) -> val = temp;
}

void	swap_b(t_dll *topb)
{
	int	temp;

	if (count_dll(topb) < 2)
		return ;
	temp = topb -> val;
	topb -> val = (topb -> lower) -> val;
	(topb -> lower) -> val = temp;
}

void	swap_ab(t_dll *topa, t_dll *topb)
{
	swap_a(topa);
	swap_b(topb);
}

void	push_a(t_dll **topb, t_dll **topa)
{
	t_dll	*temp;

	if (!*topb)
		return ;
	add_top_node(topa, new_node((*topb) -> val));
	rm_top_node(topb);
}

void	push_b(t_dll **topa, t_dll **topb)
{
	t_dll	*temp;

	if (!*topa)
		return ;
	add_top_node(topb, new_node((*topa) -> val));
	rm_top_node(topa);
}

void	rotate_a(t_dll **top)
{
	if (!*top)
		return ;
	*top = (*top) -> lower;
}

void	rotate_b(t_dll **top)
{
	if (!*top)
		return ;
	*top = (*top) -> lower;
}

void	rotate_ab(t_dll **topa, t_dll **topb)
{
	rotate_a(topa);
	rotate_b(topb);
}

void	rev_rot_a(t_dll **top)
{
	if (!*top)
		return ;
	*top = (*top) -> higher;
}

void	rev_rot_b(t_dll **top)
{
	if (!*top)
		return ;
	*top = (*top) -> higher;
}

void	rev_rot_ab(t_dll **topa, t_dll **topb)
{
	rev_rot_a(topa);
	rev_rot_b(topb);
}

static long	ft_digtoi(const char *nptr)
{
	long	res;

	res = 0;
	while (*nptr >= 48 && *nptr <= 57)
	{
		res = (res * 10) + *nptr - 48;
		nptr++;
	}
	return (res);
}

long	my_atoi(char *str)
{
	long	res;

	if (*str == '-')
		res = ft_digtoi(str + 1) * -1;
	else
		res = ft_digtoi(str);
	return (res);
}

int	is_validlim(long i)
{
	if (i > INT_MAX || i < INT_MIN)
		return (0);
	else
		return (1);
}

// tops after leading empty spaces
int	is_validnum(char *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (0);
	if (str[i] == '-')
		i++;
	if (isdigit(str[i]))			//write own function for isdigit
	{
		while (isdigit(str[i]))
			i++;
		if (str[i] == ' ' || !str[i])
			return (i);
	}
	return (-1);
}

// checks for wrong chars and returns number of numbers
t_dll	*single_input(char *str)
{
	t_dll	*top;
	long	temp;

	top = 0;
	while (str)
	{
		while (*str == ' ')
			str++;
		if (is_validnum(str) > 0)
		{
			temp = my_atoi(str);
			str = str + is_validnum(str);
			if (is_validlim(temp))
				add_last(&top, (int) temp);
			else
				free_list(top);
		}
		else if (!is_validnum(str) && top)
			return (top);
		else
			free_list(top);
	}
	return (top);
}

t_dll	*multi_input(int argc, char *argv[])
{
	t_dll	*top;
	int		i;
	long	temp;

	top = 0;
	i = 1;
	while (i < argc)
	{
		if (is_validnum(argv[i]) > 0)
		{
			temp = my_atoi(argv[i]);
			if (is_validlim(temp))
				add_last(&top, (int) temp);
			else
				free_list(top);
		}
		else
			free_list(top);
		i++;
	}
	return (top);
}

void	find_dups(t_dll *top)
{
	int		*seen;
	int		i;
	int		j;
	t_dll	*ptr;

	seen = malloc(sizeof(int) * count_dll(top));
	i = 0;
	if (!seen)
		free_list(top);
	ptr = top;
	while (ptr)
	{
		j = 0;
		while (j < i)
		{
			if (ptr -> val == seen[j++])
			{
				free(seen);
				free_list(top);
			}
		}
		seen[i++] = ptr -> val;
		ptr = ptr -> lower;
	}
	free(seen);
}

t_dll	*check_input(int argc, char *argv[])
{
	t_dll	*top;

	if (argc == 1)
		exit(EXIT_FAILURE);
	else if (argc == 2)
		top = single_input(argv[1]);
	else if (argc > 2)
		top = multi_input(argc, argv);
	find_dups(top);
	return (top);
}

int	push_swap(t_dll *stack_a)
{
	t_dll	*stack_b;

	stack_b = 0;
	close_dll(stack_a);
	push_b(&stack_a, &stack_b);
	push_b(&stack_a, &stack_b);
	push_b(&stack_a, &stack_b);
	push_b(&stack_a, &stack_b);
	push_b(&stack_a, &stack_b);
	push_a(&stack_b, &stack_a);
	push_a(&stack_b, &stack_a);
	push_a(&stack_b, &stack_a);
	push_a(&stack_b, &stack_a);
	print_stacks(stack_a, stack_b);		// ---------> continue here
	return (1);
}
	

int	main(int argc, char *argv[])
{
	t_dll *top = check_input(argc, argv);
	printl(top);
	push_swap(top);
	return (0);
}
