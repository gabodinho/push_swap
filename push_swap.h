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
void	free_list(t_dll *top);
void	printl(t_dll *top);
void	print_stacks(t_dll *a, t_dll *b);
void	rm_top_node(t_dll **top);
void	add_top_node(t_dll **top, t_dll *node);
void	swap_a(t_dll *topa);
void	swap_b(t_dll *topb);
void	swap_ab(t_dll *topa, t_dll *topb);
void	push_a(t_dll **a, t_dll **b);
void	push_b(t_dll **a, t_dll **b);
void	rotate_a(t_dll **a, t_dll **b);
void	rotate_b(t_dll **a, t_dll **b);
void	rotate_ab(t_dll **a, t_dll **b);
void	rev_rot_a(t_dll **a, t_dll **b);
void	rev_rot_b(t_dll **a, t_dll **b);
void	rev_rot_ab(t_dll **a, t_dll **b);
static long	ft_digtoi(const char *nptr);
long	my_atoi(char *str);
int	is_validlim(long i);
int	is_validnum(char *str);
t_dll	*single_input(char *str);
t_dll	*multi_input(int argc, char *argv[]);
void	find_dups(t_dll *top);
t_dll	*check_input(int argc, char *argv[]);
int	get_offset(t_dll *a);
int	get_steps(t_dll *stack, int x);
int	get_pos_b(t_dll *b, int x);
int	get_pos_a(t_dll *b, int x);
int	ft_abs(int i);
int	get_val(t_dll *stack, int idx);
int	ft_max(int a, int b);
int	ft_min(int a, int b);
int	get_nmoves(int a, int b);
void	fill_zeros(int *ar);
void	get_moves(int na, int nb, int mv[3]);
void	get_opt(t_dll **a, t_dll **b, int mv[3]);
fptr get_fptr(int mv, int i);
void	fill_b_ii(t_dll **a, t_dll **b);
void	sort_three(t_dll **a, t_dll **b);
void	final_rot(t_dll **a, t_dll **b);
void	fill_a(t_dll **a, t_dll **b);
int	push_swap(t_dll *stack_a);
	
int	main(int argc, char *argv[]);

#endif // GENERATED_HEADER_H
