/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:44:38 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/16 00:21:27 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *find_cmd
void child1 (t_pipex *pipex,char **argv,char **envp)
{
	if (dup2(pipex->infile,STDIN_FILENO) < 0) //to duplicate infile and replace stdin with the duplicate/so stdin points to infile
		ft_msg_error("Error\n Wrong dup to infile");
	if (dup2(pipex->end[1],STDOUT_FILENO)< 0)
		ft_msg_error ("Error\n Wrong dup to pipe end[1]");
	if (close(pipex->end[0]) < 0)
		ft_msg_error ("Error\n Wrong close of pipe end[0]")
	if (close(pipex->end[1])< 0)
		t_msg_error ("Error\n Wrong close of pipe end[1]")
	pipex->cmd_args =ft_split(argv[2],' ');

}
