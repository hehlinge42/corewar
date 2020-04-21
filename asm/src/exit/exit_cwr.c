/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cwr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 14:08:31 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/17 18:59:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"

void	free_labels(t_head *labels)
{
	t_head	*refs_head;
	t_lst	*label_lst;
	t_label	*label;

	label_lst = labels->first;
	while (label_lst)
	{
		label = label_lst->content;
		label_lst = label_lst->next;
		refs_head = &label->refs;
		ft_lstfree(&refs_head, FREE_BOTH, KEEP_HEAD);
	}
	ft_lstfree(&labels, FREE_BOTH, KEEP_HEAD);
}

void	exit_cwr(t_cwr *cwr)
{
	free_labels(&cwr->labels);
	if (cwr->file)
		easyfree((void **)&cwr->file);
	if (cwr->file_cor)
		easyfree((void **)&cwr->file_cor);
	if (cwr->cpy)
		easyfree((void **)&cwr->cpy);
}

void	set_context(t_cwr *cwr, char **context, int *context_len,
	int context_opt)
{
	t_token		token;

	*context = "";
	*context_len = 0;
	if (context_opt == CWR_ERR_LINE)
	{
		*context_len = cwr->line_len;
		*context = cwr->file + cwr->line_start;
	}
	else if (context_opt == CWR_ERR_CHR)
	{
		*context_len = 1;
		*context = cwr->file + cwr->pos;
	}
	else if (context_opt == CWR_ERR_TOKEN)
	{
		token = cwr->line->token[cwr->line->token_pos];
		*context_len = token.len;
		*context = token.content;
	}
}

int		cwr_error(t_cwr *cwr, char *msg, int context_opt)
{
	char	*context;
	int		context_len;

	set_context(cwr, &context, &context_len, context_opt);
	if (context_opt == CWR_ERR_NO_POS)
		ft_dprintf(2, "error - %s\n", msg, context_len, context);
	else
		ft_dprintf(2, "error at [%d][%d] - %s '%.*s'\n", cwr->line_nb,
			cwr->pos - cwr->line_start + 1, msg, context_len, context);
	return (EXIT_FAILURE);
}
