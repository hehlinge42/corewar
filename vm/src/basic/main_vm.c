/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:21:40 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/18 19:33:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int		main(int argc, char **argv)
{
	t_vm	vm;
	t_dump	dump;
	int		ret;

	ft_memset(&vm, 0, sizeof(vm));
	init_structs_vm(&vm, &dump);
	if ((ret = parse_args(&vm, argc, argv)) == EXIT_SUCCESS)
	{
		log_players(&vm);
		if ((ret = process_loop(&vm)) == EXIT_SUCCESS)
			log_winner(&vm);
		else
			ft_errors_print();
	}
	else
		ft_errors_print();
	exit_vm(vm);
	return (ret);
}
