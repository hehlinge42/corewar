/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:33:11 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/18 16:42:53 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void	exit_vm(t_vm vm)
{
	t_process	*process;
	t_lst		*process_lst;

	if (vm.processes)
	{
		process_lst = vm.processes->first;
		while (process_lst)
		{
			process = process_lst->content;
			process_lst = process_lst->next;
			easyfree((void **)&process);
		}
		ft_lstfree(&vm.processes, FREE_LINKS, FREE_HEAD);
	}
}
