/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 01:01:18 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/12/24 01:42:08 by ggiertzu         ###   ########.fr       */
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

typedef void    (*fptr)(t_dll **, t_dll **);

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
/*
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
*/

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

	printf("\n A\tB\n");
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

void	swap_a(t_dll *topa)
{
	int	temp;

	if (count_stack(topa) < 2)
		return ;
	temp = topa -> val;
	topa -> val = (topa -> lower) -> val;
	(topa -> lower) -> val = temp;
}

void	swap_b(t_dll *topb)
{
	int	temp;

	if (count_stack(topb) < 2)
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

void	push_a(t_dll **a, t_dll **b)
{
	t_dll	*temp;

	if (!*b)
		return ;
	add_top_node(a, new_node((*b) -> val));
	rm_top_node(b);
}

void	push_b(t_dll **a, t_dll **b)
{
	t_dll	*temp;

	if (!*a)
		return ;
	add_top_node(b, new_node((*a) -> val));
	rm_top_node(a);
}

void	rotate_a(t_dll **a, t_dll **b)
{
	(void)	b;
	if (!*a)
		return ;
	*a = (*a) -> lower;
}

void	rotate_b(t_dll **a, t_dll **b)
{
	(void)	a;
	if (!*b)
		return ;
	*b = (*b) -> lower;
}

void	rotate_ab(t_dll **a, t_dll **b)
{
	rotate_a(a, b);
	rotate_b(a, b);
}

void	rev_rot_a(t_dll **a, t_dll **b)
{
	(void)	b;
	if (!*a)
		return ;
	*a = (*a) -> higher;
}

void	rev_rot_b(t_dll **a, t_dll **b)
{
	if (!*b)
		return ;
	*b = (*b) -> higher;
}

void	rev_rot_ab(t_dll **a, t_dll **b)
{
	rev_rot_a(a, b);
	rev_rot_b(a, b);
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

	seen = malloc(sizeof(int) * count_stack(top));
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
		if (temp > (ptr -> lower) -> val)
			return (i + 1);
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

// given that b is sorted (desc), this func returns the postition of x in b
int	get_pos_b(t_dll *b, int x)
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

int	ft_abs(int i)
{
	if (i < 0)
		return (i * -1);
	else
		return (i);
}

int	get_val(t_dll *stack, int idx)
{
	int	i;

	i = 1;
	while (i++ < idx)
		stack = stack -> lower;
	return (stack -> val);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
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

void	fill_zeros(int *ar)
{
	int	i;

	i = 0;
	while (i < 3)
		ar[i++] = 0;
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
//		printf("pos: %d, A: %d, C: %d, res: %d\n", ar[0], ar[1], ar[2], get_nmoves(ar[1], ar[2]));
	}
	get_moves(ar[4], ar[5], mv);
	printf("pos: %d, A: %d, C: %d\n", ar[3], ar[4], ar[5]);
	printf("pos: %d, A: %d, B: %d, C: %d\n", ar[3], mv[0], mv[1], mv[2]);
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


int	fill_b_ii(t_dll **a, t_dll **b)
{
	int	mv[3];
	fptr	func_ptr;
	int	i;
	int	j;
	static int count;

	while (count_stack(*a) > 3)
	{
		get_opt(a, b, mv);
		i = 0;
		while (i < 3)
		{
			func_ptr = get_fptr(mv[i], i);
			j = 0;
			while (j++ < ft_abs(mv[i]))
			{
				func_ptr(a, b);
				count++;
			}
			i++;
		}
		push_b(a, b);
		count++;
		print_stacks(*a, *b);
	}
	return (count);
}

void	sort_three(t_dll **a, t_dll **b)
{
	int	ar[3];

	while (1)
	{
		ar[0] = (*a) -> val;
		ar[1] = (*a) -> lower -> val;
		ar[2] = (*a) -> higher -> val;
		if ((ar[1] > ar[2] && ar[2] > ar[0]) || (ar[2] > ar[0] && ar[0] > ar[1]))
			swap_a(*a);
		if ((ar[0] > ar[2] && ar[2] > ar[1]) || (ar[0] > ar[1] && ar[1] > ar[2]))
			rotate_a(a, b);
		if (ar[1] > ar[0] && ar[0] > ar[2])
			rev_rot_a(a, b);
		if (!(ar[0] > ar[1] && ar[1] > ar[2]))
			break;
	}
}

void	final_rot(t_dll **a, t_dll **b)
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

void	fill_a(t_dll **a, t_dll **b)
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
		print_stacks(*a, *b);
	}
}

int	push_swap(t_dll *stack_a)
{
	t_dll	*stack_b;

	stack_b = 0;
	close_dll(stack_a);
	push_b(&stack_a, &stack_b);
	push_b(&stack_a, &stack_b);
int res = fill_b_ii(&stack_a, &stack_b);
	sort_three(&stack_a, &stack_b);
	fill_a(&stack_a, &stack_b);
	final_rot(&stack_a, &stack_b);
//	rotate_ab(&stack_a, &stack_b);	
	printf("total ops: %d\n", res + 2);
	printf("offset: %d\n", get_offset(stack_a));
	print_stacks(stack_a, stack_b);		// ---------> continue here
//	printf("\npos: %d\n", get_pos_b(stack_a, 45));
//	get_opt(stack_a, stack_b);
	return (1);
}
	

int	main(int argc, char *argv[])
{
	t_dll *top = check_input(argc, argv);
	printl(top);
	push_swap(top);
	return (0);
}
