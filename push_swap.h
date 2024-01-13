#ifndef GENERATED_HEADER_H
#define GENERATED_HEADER_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <ft_printf.h>
typedef struct	s_dll
{
	int				val;
	struct s_dll	*higher;
	struct s_dll	*lower;
} t_dll;
typedef void    (*fptr)(t_dll **, t_dll **);
t_dll	*new_node(int val);
int	count_stack(t_dll *start);
void	del_list(t_dll *ref);
void	add_last(t_dll **ref, int val);
void	close_dll(t_dll *top);
void	throw_error(int val);
void	printl(t_dll *top);
void	print_stacks(t_dll *a, t_dll *b);
void	swap_a(t_dll *topa);
void	push_a(t_dll **a, t_dll **b);
void	push_b(t_dll **a, t_dll **b);
void	rotate_a(t_dll **a, t_dll **b);
void	rotate_b(t_dll **a, t_dll **b);
void	rotate_ab(t_dll **a, t_dll **b);
void	rev_rot_a(t_dll **a, t_dll **b);
void	rev_rot_b(t_dll **a, t_dll **b);
void	rev_rot_ab(t_dll **a, t_dll **b);
long	my_atoi(char *str);
int	is_validlim(long i);
int	is_validnum(char *str);
t_dll	*check_input(int argc, char *argv[]);
int	get_offset(t_dll *a);
int	get_steps(t_dll *stack, int x);
int	get_pos_a(t_dll *b, int x);
int	ft_abs(int i);
int	get_val(t_dll *stack, int idx);
int	get_nmoves(int a, int b);
void	get_moves(int na, int nb, int mv[3]);
void	get_opt(t_dll **a, t_dll **b, int mv[3]);
fptr get_fptr(int mv, int i);
int	push_swap(t_dll **stack_a);
	
int	main(int argc, char *argv[]);

#endif // GENERATED_HEADER_H
