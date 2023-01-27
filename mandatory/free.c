/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:05:08 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/27 00:23:58 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_msg_error(char *str)
{
	perror (str);
	exit (1);
}

void	ft_close(t_pipex *pipex)
{
	if (close(pipex->end[1]) == -1)
		ft_msg_error ("Error\n Wrong close of pipe end[1]");
	if (close(pipex->end[0]) == -1)
		ft_msg_error ("Error\n Wrong close of pipe end[0]");
	if (close(pipex->infile) == -1)
		ft_msg_error("Error\n Wrong close infile");
	if (close(pipex->outfile) == -1)
		ft_msg_error("Error\n Wrong close outfile");
	free_array(pipex->cmd_paths);
	free_array (pipex->cmd1_args);
	free_array(pipex->cmd2_args);
}
