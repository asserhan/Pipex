/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 01:54:56 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/27 05:32:47 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		if (access(my_cmd, F_OK | X_OK) == 0)
			return (my_cmd);
		free (my_cmd);
	}
	return (NULL);
}

void	execute_cmd(char *cmd, t_pipex *pipex, char **envp)
{
	get_path(pipex, envp);
	pipex->cmd_arg = ft_split(cmd, ' ');
	cmd = pipex->cmd_arg[0];
	if (pipex->paths != NULL && ft_strchr(pipex->cmd_arg[0], '/') == NULL)
		cmd = get_cmd_path (pipex->cmd_paths, pipex->cmd_arg[0]);
	if (!cmd)
	{
		free_array(pipex->cmd_arg);
		free (cmd);
		write(2, "Command not found\n", 19);
		exit (127);
	}
	execve(cmd, pipex->cmd_arg, envp);
	perror("pipex");
	exit(127);
}

void	multi_pipe(char *cmd, t_pipex *pipex, char **envp)
{
	int	end[2];
	int	pid;

	if (pipe(end) == -1)
		ft_msg_error ("Error with pipe\n ");
	pid = fork();
	if (pid == -1)
		ft_msg_error("Erro \nNo child process is created");
	if (pid == 0)
	{
		close(end[0]);
		if (dup2(end[1], STDOUT_FILENO) == -1)
			ft_msg_error ("Error\nWrong dup to pipe end[1]");
		close(end[1]);
		execute_cmd(cmd, pipex, envp);
	}
	else
	{
		close(end[1]);
		if (dup2(end[0], STDIN_FILENO) == -1)
			ft_msg_error ("Error\nWrong dup to pipe end[0]");
		close(end[0]);
		waitpid(pid, NULL, 0);
	}
}
