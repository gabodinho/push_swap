/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 01:01:18 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/12/08 00:39:18 by ggiertzu         ###   ########.fr       */
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
	if (ref)
	{
		del_list(ref -> next);
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
	while (ptr -> next)
		ptr = ptr -> next;
	if (!new)
		del_list(*ref);
	ptr -> next = new;
	new -> prev = ptr;
}


int	count_dll(t_dll	*start)
{
	t_dll	*ptr;
	int		i;

	ptr = start;
	i = 0;
	while (ptr)
	{
		i++;
		ptr = ptr -> next;
	}
	return (i);
}

void	throw_error(int val)
{
	if (val == EXIT_FAILURE)
	{
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
}

void	free_list(t_dll *start)
{
	del_list(start);
	throw_error(EXIT_FAILURE);
}

// delete this function for final version
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

// starts after leading empty spaces
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
	t_dll	*start;
	long	temp;

	start = 0;
	while (str)
	{
		while (*str == ' ')
			str++;
		if (is_validnum(str) > 0)
		{
			temp = my_atoi(str);
			str = str + is_validnum(str);
			if (is_validlim(temp))
				add_last(&start, (int) temp);
			else
				free_list(start);
		}
		else if (!is_validnum(str) && start)
			return (start);
		else
			free_list(start);
	}
	return (start);
}

t_dll	*multi_input(int argc, char *argv[])
{
	t_dll	*start;
	int		i;
	long	temp;

	start = 0;
	i = 1;
	while (i < argc)
	{
		if (is_validnum(argv[i]) > 0)
		{
			temp = my_atoi(argv[i]);
			if (is_validlim(temp))
				add_last(&start, (int) temp);
			else
				free_list(start);
		}
		else
			free_list(start);
		i++;
	}
	return (start);
}

t_dll	*check_input(int argc, char *argv[])
{
	if (argc == 1)
		exit(EXIT_FAILURE);
	else if (argc == 2)
		return (single_input(argv[1]));
	else if (argc > 2)
		return (multi_input(argc, argv));
}

void	find_dups(t_dll *start)
{
	int		*seen;
	int		i;
	int		j;
	t_dll	*ptr;

	seen = malloc(sizeof(int) * count_dll(start));
	i = 0;
	if (!seen)
		free_list(start);
	ptr = start;
	while (ptr)
	{
		j = 0;
		while (j < i)
		{
			if (ptr -> val == seen[j++])
			{
				free(seen);
				free_list(start);
			}
		}
		seen[i++] = ptr -> val;
		ptr = ptr -> next;
	}
	free(seen);
}

int	main(int argc, char *argv[])
{
	t_dll *start = check_input(argc, argv);
	find_dups(start);
	printl(start);
	del_list(start);
	printl(start);
	return (0);
}
