/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:06:47 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/01/12 23:06:52 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

static void	free_list(t_dll *top)
{
	del_list(top);
	{
		ft_printf("Error\n");
		exit(EXIT_FAILURE);
	}
}

// checks for wrong chars and returns number of numbers
static t_dll	*single_input(char *str)
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

static t_dll	*multi_input(int argc, char *argv[])
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

static void	find_dups(t_dll *top)
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
