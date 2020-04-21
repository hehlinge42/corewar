/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prog.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:20:45 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/17 18:37:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"

int		parse_line(t_cwr *cwr)
{
	ft_memset(cwr->line, 0, sizeof(*cwr->line));
	if (parse_line_tokens(cwr, cwr->line, cwr->line->token) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	else if (check_tokens(cwr, cwr->line) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	else if (get_tokens_contents(cwr, cwr->line) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	else if (line_to_prog(cwr, cwr->line) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		parse_prog(t_cwr *cwr)
{
	while (cwr->pos < cwr->file_len)
	{
		skip_to_eol(cwr);
		if (!cwr_eol(cwr->file[cwr->pos]) && cwr->file[cwr->pos]
			!= COMMENT_CHAR)
		{
			if (parse_line(cwr) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
		if (cwr->line_len != 0)
			cwr->pos += cwr->line_len + 1;
		if (cwr->file[cwr->pos] == COMMENT_CHAR)
			skip_comment(cwr);
		if (cwr->file[cwr->pos] != 0 && !cwr_eol(cwr->file[cwr->pos]))
		{
			return (cwr_error(cwr,
				"wrong pos after go_to_endline / get_tokens", NONE));
		}
		update_line_nb(cwr, cwr->file[cwr->pos]);
	}
	return (EXIT_SUCCESS);
}
