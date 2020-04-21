/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charge_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 18:45:00 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/18 19:17:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"
#include <unistd.h>

t_player	*get_player(t_vm *vm, t_process *process)
{
	unsigned	nb_player;

	nb_player = reg_to_long_unsigned(process->reg_tab[0]);
	nb_player *= ZAZ_MODE;
	if (nb_player > MAX_PLAYERS)
		return (NULL);
	return (&vm->player[nb_player]);
}

void		set_player_tab(t_vm *vm)
{
	unsigned	pos;
	unsigned	new_pos;

	pos = MAX_PLAYERS + 1;
	while (pos <= MAX_PLAYERS + vm->nb_players)
	{
		if (vm->player[pos].id)
		{
			new_pos = 1;
			while (vm->player[new_pos].id)
				new_pos++;
			ft_memcpy(vm->player + new_pos, vm->player + pos, sizeof(t_player));
			vm->player[new_pos].id = new_pos * ZAZ_MODE;
		}
		pos++;
	}
}

int			charge_players(t_vm *vm)
{
	size_t		distance;
	size_t		pos;
	unsigned	charged;
	t_process	*process;

	set_player_tab(vm);
	distance = MEM_SIZE / vm->nb_players;
	charged = 1;
	pos = 0;
	if (!(vm->processes = ft_lstnew_head()))
		return (ft_error("Malloc error\n"));
	while (charged <= vm->nb_players)
	{
		ft_memcpy(vm->arena + pos, vm->player[charged].prog
			, vm->player[charged].prog_size);
		if ((add_process(vm, pos)) != EXIT_SUCCESS)
			return (ft_error("Malloc error\n"));
		process = vm->processes->first->content;
		long_unsigned_to_reg(process->reg_tab[0], vm->player[charged].id);
		update_process_player(process);
		pos += distance;
		++charged;
	}
	vm->winner = vm->player[charged - 1].id * ZAZ_MODE;
	return (EXIT_SUCCESS);
}
