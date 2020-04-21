/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:51:51 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/17 14:24:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"

int		check_token(t_cwr *cwr, int current)
{
	int		next;

	next = TOKEN_END;
	if (cwr->line->token_pos < TOKEN_MAX - 1)
		next = cwr->line->token[cwr->line->token_pos + 1].type;
	if ((current == TOKEN_INST || current == TOKEN_SEP) && next != TOKEN_ARG)
		return (cwr_error(cwr, "missing arg after token: ", CWR_ERR_TOKEN));
	if (current == TOKEN_ARG && next != TOKEN_SEP && next != TOKEN_END)
		return (cwr_error(cwr, "missing separator after arg: ", CWR_ERR_TOKEN));
	if (cwr->line->token_pos == TOKEN_MAX - 1 && current != TOKEN_ARG
		&& current != TOKEN_LABEL)
	{
		return (cwr_error(cwr, "line must end with label or argument",
			CWR_ERR_LINE));
	}
	return (EXIT_SUCCESS);
}

int		check_tokens(t_cwr *cwr, t_line *line)
{
	t_token	*token;

	line->token_pos = line->first_token;
	token = &line->token[line->token_pos];
	if (token->type == TOKEN_LABEL)
		token = &line->token[++line->token_pos];
	if (line->token_pos != TOKEN_MAX && token->type != TOKEN_INST)
	{
		return (cwr_error(cwr, "line must start with label/instruction: ",
			CWR_ERR_LINE));
	}
	while (line->token_pos < TOKEN_MAX)
	{
		if (check_token(cwr, token->type) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		++token;
		++line->token_pos;
	}
	return (EXIT_SUCCESS);
}
