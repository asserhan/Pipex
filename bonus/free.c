/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 02:04:15 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/23 06:19:39 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void free_array(char **array)
{
	int i;
	i = -1;
	while (array[++i])
		free(array[i]);
	free (array);
}

void ft_close (t_pipex *pipex)
{
	if (close(pipex->end[1]) == -1)
		ft_msg_error ("Error\n Wrong close of pipe end[1]");
	if (close(pipex->end[0]) == -1)
		ft_msg_error ("Error\n Wrong close of pipe end[0]");
	unlink ("here_doc_temp");
	if (close(pipex->infile) == -1)
		ft_msg_error("Error\n Wrong close infile");
	if (close(pipex->outfile) == -1)
		ft_msg_error("Error\n Wrong close outfile");
}




