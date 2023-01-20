/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:44:38 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/20 02:36:04 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *get_cmd_path(char **path,char *command)
{
	char *my_cmd;
	int i;
	i = -1;
	while (path[++i])
	{
		my_cmd = ft_strjoin (path[i],command);
		if (access(my_cmd,F_OK | X_OK) == 0)
			return (my_cmd);
		free (my_cmd);
	}
	return (NULL);

}
void free_array(char **array)
{
	int i;
	i = -1;
	while (array[++i])
		free(array[i]);
	free (array);
}

void child1 (t_pipex pipex,char **envp)
{
	if (dup2(pipex.infile,STDIN_FILENO) == -1) //to duplicate infile and replace stdin with the duplicate/so stdin points to infile
		ft_msg_error("Error\n Wrong dup to infile");
	if (dup2(pipex.end[1],STDOUT_FILENO)== -1)
		ft_msg_error ("Error\n Wrong dup to pipe end[1]");
	if (close(pipex.end[0]) == -1)
		ft_msg_error ("Error\n Wrong close of pipe end[0]");
	pipex.cmd = get_cmd_path (pipex.cmd_paths,pipex.cmd1_args[0]);
	if (!pipex.cmd)
	{
		free_array(pipex.cmd1_args);
		free (pipex.cmd);
		ft_msg_error("Error\n Command not found");
	}
	execve(pipex.cmd,pipex.cmd1_args,envp);

}
void child2 (t_pipex pipex,char **envp)
{
	if (dup2(pipex.end[0],STDIN_FILENO)== -1)
		ft_msg_error ("Error\n Wrong dup to pipe end[0]");
	if (close(pipex.end[1]) == -1)
		ft_msg_error ("Error\n Wrong close of pipe end[1]");
	if (dup2(pipex.outfile,STDOUT_FILENO) == -1)
		ft_msg_error("Error\n Wrong dup to infile");
	pipex.cmd = get_cmd_path (pipex.cmd_paths,pipex.cmd2_args[0]);
	if (!pipex.cmd)
	{
		free_array(pipex.cmd2_args);
		free (pipex.cmd);
		ft_msg_error("Error\n Command not found");
	}
	execve(pipex.cmd,pipex.cmd2_args,envp);
}
