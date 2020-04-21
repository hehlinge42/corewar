/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:25:10 by user42            #+#    #+#             */
/*   Updated: 2020/04/17 19:11:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"
#include <fcntl.h>

int		write_to_file(t_cwr *cwr)
{
	if (write(cwr->fd, cwr->header, sizeof(header_t)) != sizeof(header_t))
		cwr_error(cwr, "Error writing to file header\n", NONE);
	if (write(cwr->fd, cwr->prog, cwr->prog_pos) != cwr->prog_pos)
		cwr_error(cwr, "Error writing to file\n", NONE);
	write(1, "Writing output to file ", ft_strlen("Writing output to file "));
	write(1, cwr->file_cor, ft_strlen(cwr->file_cor));
	write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

void	init_header(t_cwr *cwr)
{
	ft_memcpy(((header_t *)cwr->header)->comment, cwr->comment,
		cwr->len_comment);
	ft_memcpy(((header_t *)cwr->header)->prog_name, cwr->prog_name,
		cwr->len_prog_name);
	((header_t *)cwr->header)->prog_size = cwr->prog_pos;
	swap_endian((char *)&((header_t *)cwr->header)->prog_size,
		sizeof(((header_t *)cwr->header)->prog_size));
	((header_t *)cwr->header)->magic = COREWAR_EXEC_MAGIC;
	swap_endian((char *)&((header_t *)cwr->header)->magic,
		sizeof(((header_t *)cwr->header)->magic));
}

int		create_output_file(t_cwr *cwr)
{
	if (cwr->prog_pos == 0)
		cwr_error(cwr, "Must enter instructions\n", NONE);
	init_header(cwr);
	cwr->fd = open(cwr->file_cor, O_CREAT | O_TRUNC | O_APPEND | O_WRONLY,
		0644);
	if (cwr->fd == -1)
		cwr_error(cwr, "Unable to create output file\n", NONE);
	write_to_file(cwr);
	close(cwr->fd);
	return (EXIT_SUCCESS);
}
