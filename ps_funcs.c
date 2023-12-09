/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 01:01:18 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/12/09 23:00:53 by ggiertzu         ###   ########.fr       */
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

void	del_list(t_dll *ref)
{
	if (ref)
	{
		del_list(ref -> lower);
		free(ref);
		ref = 0;
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

void	rm_top_node(t_dll **top)
{
	t_dll	*temp;

	if (!*top)
		return ;
	else if (count_dll(*top) == 1)
	{
		free_list(*top);
		*top = NULL;
	}
	else
	{
		(*top -> lower) -> higher = *top -> higher;
		(*top -> higher) -> lower = *top -> lower;
		temp = *top -> lower;
		free(*top);
		*top = temp;
	}
}

void	add_top_node(t_dll **top; t_dll *node)
{
	if (*top)
	{
		temp = *top;
		node -> higher = temp -> higher;
		(temp -> higher) -> lower = node;
		temp -> higher = node;
		node -> lower = temp;
	}
	*top = node;
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

void	swap_a(t_dll *sa)
{
	int	temp;

	if (count_dll(sa) < 2)
		return ;
	temp = sa -> val;
	sa -> val = (sa -> next) -> val;
	(sa -> next) -> val = temp;
}

void	swap_b(t_dll *sb)
{
	int	temp;

	if (count_dll(sb) < 2)
		return ;
	temp = sb -> val;
	sb -> val = (sb -> next) -> val;
	(sb -> next) -> val = temp;
}

void	swap_ab(t_dll *stack_a, t_dll *stack_b)
{
	swap_a(sa);
	swap_b(sb);
}

void	push_a(t_dll **topb, t_dll **topa)
{
	t_dll	*temp;

	if (!*topb)
		return ;
	add_top_node(topa, new_node(*topb -> val));
	rm_top_node(topb);									// continue here <----
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

	close_dll(stack_a);
							// ---------> continue here
}
	

int	main(int argc, char *argv[])
{
	t_dll *top = check_input(argc, argv);
	printl(top);
	del_list(top);
	printl(top);
	return (0);
}
