/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_prog.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 11:28:13 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/17 14:27:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"
#include <unistd.h>
#include <fcntl.h>

void	make_encoding_byte(t_line *line)
{
	int i;

	i = 0;
	while (i < 3)
	{
		line->arg_type[i] == T_IND ? (line->encoding_byte ^= 0b11)
			: (line->encoding_byte ^= line->arg_type[i]);
		line->encoding_byte <<= 2;
		i++;
	}
}

int		code_and_encoding(t_cwr *cwr, t_line *line)
{
	if (cwr->prog_pos > CHAMP_MAX_SIZE)
		return (cwr_error(cwr, "program too long:", CWR_ERR_LINE));
	cwr->prog[cwr->prog_pos] = (char)line->op_code;
	if (line->rules->has_coding_byte != 0)
	{
		make_encoding_byte(line);
		if (++cwr->prog_pos > CHAMP_MAX_SIZE)
			return (cwr_error(cwr, "program too long:", CWR_ERR_LINE));
		cwr->prog[cwr->prog_pos] = (char)line->encoding_byte;
	}
	++cwr->prog_pos;
	return (EXIT_SUCCESS);
}

int		write_args(t_cwr *cwr, t_line *line, unsigned arg)
{
	int		arg_size;
	int		arg_end;
	char	content;

	arg_size = line->token[line->arg_index_token[arg]].byte_size;
	arg_end = (arg_size + cwr->prog_pos) - 1;
	if (arg_end > CHAMP_MAX_SIZE)
		return (cwr_error(cwr, "program too long:", CWR_ERR_LINE));
	while (arg_end >= cwr->prog_pos)
	{
		content = (char)line->arg[arg];
		cwr->prog[arg_end] = (char)content;
		line->arg[arg] >>= 8;
		--arg_end;
	}
	cwr->prog_pos += arg_size;
	return (EXIT_SUCCESS);
}

int		line_to_prog(t_cwr *cwr, t_line *line)
{
	unsigned i;

	i = 0;
	if (line->rules == NULL)
		return (EXIT_SUCCESS);
	if (code_and_encoding(cwr, line) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	while (i < line->arg_nb)
	{
		if (write_args(cwr, line, i) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}
