/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:44:38 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/27 01:14:56 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_path(t_pipex *pipex, char **envp)
{
	char	*temp;
	int		i;

	pipex->cmd_paths = NULL;
	i = -1;
	while (*envp && ft_strncmp("PATH", *envp, 4) != 0)
			envp++;
	if (*envp == NULL)
		return ;
	pipex->paths = *envp + 5;
	pipex->cmd_paths = ft_split(pipex->paths, ':');
	if (!pipex->cmd_paths)
		ft_msg_error("Error\n");
	while (pipex->cmd_paths[++i])
	{
		temp = pipex->cmd_paths[i];
		pipex->cmd_paths[i] = ft_strjoin(temp, "/");
		if (!pipex->cmd_paths[i])
			ft_msg_error("Error\n");
		free (temp);
	}
}

char	*get_cmd_path(char **path, char *command)
{
	char	*my_cmd;
	int		i;

	i = -1;
	if (!path)
		return (command);
	while (path[++i])
	{
		my_cmd = ft_strjoin (path[i], command);
		if (access(my_cmd, F_OK) == 0)
			return (my_cmd);
		free (my_cmd);
	}
	return (NULL);
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	if (array == NULL)
		return ;
	while (array[++i])
		free(array[i]);
	free (array);
}

void	child1(t_pipex pipex, char **argv, char **envp)
{
	if (dup2(pipex.infile, STDIN_FILENO) == -1)
		ft_msg_error("Error\n Wrong dup to infile");
	if (dup2(pipex.end[1], STDOUT_FILENO) == -1)
		ft_msg_error ("Error\n Wrong dup to pipe end[1]");
	if (close(pipex.end[0]) == -1)
		ft_msg_error ("Error\n Wrong close of pipe end[0]");
	pipex.cmd1_args = ft_split(argv[2], ' ');
	pipex.cmd = pipex.cmd1_args[0];
	if (pipex.paths != NULL && ft_strchr (pipex.cmd1_args[0], '/') == NULL)
		pipex.cmd = get_cmd_path (pipex.cmd_paths, pipex.cmd1_args[0]);
	if (!pipex.cmd)
	{
		free_array(pipex.cmd1_args);
		free (pipex.cmd);
		write(2, "Command not found\n", 19);
		exit (127);
	}
	execve(pipex.cmd, pipex.cmd1_args, envp);
	perror("pipex");
	exit(127);
}

void	child2(t_pipex pipex, char **argv, char **envp)
{
	if (dup2(pipex.end[0], STDIN_FILENO) == -1)
		ft_msg_error ("Error\n Wrong dup to pipe end[0]");
	if (close(pipex.end[1]) == -1)
		ft_msg_error ("Error\n Wrong close of pipe end[1]");
	if (dup2(pipex.outfile, STDOUT_FILENO) == -1)
		ft_msg_error("Error\n Wrong dup to infile");
	pipex.cmd2_args = ft_split(argv[3], ' ');
	pipex.cmd = pipex.cmd2_args[0];
	if (pipex.paths != NULL && ft_strchr(pipex.cmd2_args[0], '/') == NULL)
		pipex.cmd = get_cmd_path (pipex.cmd_paths, pipex.cmd2_args[0]);
	if (!pipex.cmd)
	{
		free_array(pipex.cmd2_args);
		free (pipex.cmd);
		write(2, "Command not found\n", 19);
		exit(127);
	}
	execve(pipex.cmd, pipex.cmd2_args, envp);
	perror("pipex");
	exit(127);
}
