/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 11:31:56 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/17 15:37:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"

t_label	*find_label(t_lst *label_lst, char *label_name)
{
	while (label_lst)
	{
		if (!ft_strcmp(((t_label *)label_lst->content)->name, label_name))
			return (label_lst->content);
		label_lst = label_lst->next;
	}
	return (NULL);
}

int		get_label(t_cwr *cwr, t_label **label, char *label_name)
{
	*label = find_label(cwr->labels.first, label_name);
	if (*label != NULL)
		return (EXIT_SUCCESS);
	else if (!(*label = alloc_new_label(label_name, -1)))
		return (cwr_error(cwr, "could not allocate label: ", CWR_ERR_TOKEN));
	else if (!ft_lstadd_new(&cwr->labels, *label))
		return (cwr_error(cwr, "could not add label to list: ", CWR_ERR_TOKEN));
	return (EXIT_SUCCESS);
}

int		add_label(t_cwr *cwr, t_token *token, unsigned label_prog_pos)
{
	t_label	*label;
	t_head	*refs_head;

	token->content[token->len - 1] = 0;
	if (get_label(cwr, &label, token->content) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	else if (label->prog_pos != -1U)
		return (cwr_error(cwr, "duplicate label: ", CWR_ERR_TOKEN));
	label->prog_pos = label_prog_pos;
	if (label->refs.first)
	{
		label->prog_pos = cwr->prog_line_start;
		fill_in_refs(cwr, label->refs.first, label->prog_pos);
		refs_head = &label->refs;
		ft_lstfree(&refs_head, FREE_BOTH, KEEP_HEAD);
	}
	return (EXIT_SUCCESS);
}
