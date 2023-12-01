/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 01:01:18 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/12/01 16:29:22 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static long	ft_digtoi(const char *nptr)
{
	long	res;

	res = 0;
	while (ft_isdigit(*nptr))
	{
		res = (res * 10) + *nptr - 48;
		nptr++;
	}
	return (res);
}

int	my_atoi(char *str, int *array)
{
	int	sign;
	long	res;

	sign = 1;
	while (*str)
	{
		if (*str == '-')
		{
			sign == -1;
			res = ft_digtoi(str + 1);
		}
		else
			res = ft_digtoi(str);

	return (sign * res)




int	*get_array(int len, char *str)
{
	int	*res;
	int	i;
	long	temp;

	res = malloc(sizeof(int) * (len + 1));
	i = 0;
	if (!res)
		throw_error();
	while (*str)
	{
		while (*str == ' ')
			str++;
		temp = my_atoi(str, res);
		if (temp > INT_MAX || temp < INT_MIN)
		{
			free(res);
			throw_error();
		}
		res[i] = int(temp);
		i++;
		while (ft_isdigit(*str))
			str++;
	}
	res[i] == 0;
	return (res);
}

int	*read_input(char *str)
{
	int		prev;
	int		count;
	char	*str_cpy;

	prev = 0;
	count = 0;
	str_cpy = str;
	while (*str)
	{
		if(ft_isdigit(*str))
		{
			if (!prev)
			{
				prev = 1;
				count++;
			}
		}
		else if (*str == ' ')
			prev = 0;
		else
			throw_error();
		str++;
	}
	return (get_array(count, str_cpy));
}

int	*check_input(int argc, char *argv[])
{
	int	*stack_a;

	if (argc == 1)
		exit(EXIT_FAILURE);
	if (argc == 2)
		stack_a = read_string(argv[1]);
	if (argc > 2)
		stack_a = read_input(arg++);
	return (stack_a);
}

int	main(int argc, char *argv[])
{
	// stack_a = input_check(argc, argv)

