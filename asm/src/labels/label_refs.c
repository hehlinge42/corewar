/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_ref.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:36:36 by skpn              #+#    #+#             */
/*   Updated: 2020/04/17 15:37:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"

int		add_ref(t_cwr *cwr, int *arg, t_token *token)
{
	t_label	*label;
	t_ref	*ref;

	token->content[token->len] = 0;
	while (token->content[0] == LABEL_CHAR || token->content[0] == DIRECT_CHAR)
		++token->content;
	if (get_label(cwr, &label, token->content) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (label->prog_pos != -1U)
	{
		*arg = label->prog_pos - cwr->prog_line_start;
	}
	else
	{
		ref = alloc_new_ref(token->byte_size, cwr->prog_line_start,
			cwr->prog_pos, token->content_pos);
		if (ref == NULL)
			return (cwr_error(cwr, "could not allocate ref: ", CWR_ERR_TOKEN));
		if (!ft_lstadd_new(&label->refs, ref))
			return (cwr_error(cwr, "could not add ref to label: ",
				CWR_ERR_TOKEN));
	}
	return (EXIT_SUCCESS);
}

int		check_remaining_refs(t_cwr *cwr)
{
	t_lst	*label_lst;
	t_label *label;
	t_token	*token;

	label_lst = cwr->labels.last;
	while (label_lst)
	{
		label = label_lst->content;
		label_lst = label_lst->prev;
		if (label->refs.last)
		{
			cwr->line->token_pos = 0;
			token = &cwr->line->token[cwr->line->token_pos];
			token->content = label->name;
			token->len = ft_strlen(label->name);
			return (cwr_error(cwr, "undefined label for ref: ", CWR_ERR_TOKEN));
		}
	}
	return (EXIT_SUCCESS);
}

void	fill_in_refs(t_cwr *cwr, t_lst *ref_lst, unsigned label_pos)
{
	t_ref	*ref;
	int		*int_value;
	short	*short_value;

	while (ref_lst)
	{
		ref = ref_lst->content;
		ref_lst = ref_lst->next;
		if (ref->type_size == 2)
		{
			short_value = (short *)(cwr->prog + ref->prog_pos);
			*short_value = label_pos - ref->prog_line_start;
		}
		else
		{
			int_value = (int *)(cwr->prog + ref->prog_pos);
			*int_value = label_pos - ref->prog_line_start;
		}
		swap_endian(cwr->prog + ref->prog_pos, ref->type_size);
	}
}
