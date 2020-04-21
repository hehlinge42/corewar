/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:51:24 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 22:25:04 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int		ft_strcmp_slow(const char *s1, const char *s2)
{
	unsigned const char		*cpy_s1;
	unsigned const char		*cpy_s2;

	cpy_s1 = (unsigned const char *)s1;
	cpy_s2 = (unsigned const char *)s2;
	while (*cpy_s1 == *cpy_s2 && *cpy_s1 != '\0' && *cpy_s2 != '\0')
	{
		cpy_s1++;
		cpy_s2++;
	}
	return (*cpy_s1 - *cpy_s2);
}

int		get_opt_nb(t_vm *vm, char *arg)
{
	unsigned	opt_nb;

	opt_nb = 0;
	opt_nb = 0;
	while (opt_nb < NB_OPTIONS)
	{
		if (!ft_strcmp_slow(arg, vm->option[opt_nb].opt_name))
			return (opt_nb);
		opt_nb++;
	}
	return (NB_OPTIONS);
}

int		parse_args(t_vm *vm, int argc, char **argv)
{
	unsigned	arg;
	unsigned	opt_nb;
	int			check_error;

	check_error = 0;
	arg = 1;
	if (argc < 2)
		return (ft_error(ERR_NO_ARGS));
	while (arg < (unsigned)argc)
	{
		opt_nb = get_opt_nb(vm, argv[arg]);
		if ((check_error = vm->option[opt_nb].parse_func(vm, argv, &arg))
			!= EXIT_SUCCESS)
			return (check_error);
	}
	if (vm->nb_players == 0)
		return (ft_error(ERR_NO_PLAYERS));
	if ((check_error = charge_players(vm)) != EXIT_SUCCESS)
		return (check_error);
	return (EXIT_SUCCESS);
}
