/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 05:15:50 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/25 20:01:16 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex_bonus.h"

void ft_msg_error (char *str)
{
	perror (str);
	exit (1);
}

void execute_cmd(char *cmd,t_pipex *pipex,char **envp)
{
	get_path(pipex,envp);
	pipex->cmd_arg = ft_split(cmd,' ');
	cmd = get_cmd_path (pipex->cmd_paths,pipex->cmd_arg[0]);
	if (!cmd)
	{
		free_array(pipex->cmd_arg);
		free (cmd);
		ft_msg_error("Error\n Command not found");
	}
	if (execve(cmd,pipex->cmd_arg,envp) == -1)
		ft_msg_error("Error\n program has not executed");
	free_array(pipex->cmd_arg);
	free_array(pipex->cmd_paths);
	free(cmd);

}

void multi_pipe (char *cmd,t_pipex *pipex,char **envp)
{
	int end[2];
	int pid;
	if (pipe(end) == -1)
		ft_msg_error ("Error with pipe\n ");
	pid = fork();
	if (pid == -1)
		ft_msg_error("Error \n  No child process is created");
	if (pid == 0)
	{
		if (close(end[0]) == -1)
			ft_msg_error ("Error\n Wrong close of pipe end[0]");
		if (dup2(end[1],STDOUT_FILENO) == -1)
			ft_msg_error ("Error\n Wrong dup to pipe end[1]");
		if (close(end[1]) == -1)
			ft_msg_error ("Error\n Wrong close of pipe end[1]");
		execute_cmd(cmd,pipex,envp);

	}
	else
	{
		if (close(end[1]) == -1)
			ft_msg_error ("Error\n Wrong close of pipe end[1]");
		if (dup2(end[0],STDIN_FILENO) == -1)
			ft_msg_error ("Error\n Wrong dup to pipe end[0]");
		if (close(end[0]) == -1)
			ft_msg_error ("Error\n Wrong close of pipe end[0]");
		waitpid(pid,NULL,0);
	}
}
int main(int argc,char **argv,char **envp)
{

	t_pipex pipex;

	if (argc < 5 )
		ft_msg_error("Error\n Wrong argument");
	if (ft_strncmp(argv[1],"here_doc",9) == 0)
	{
		pipex.here_doc = 3; //argv[3]
		here_doc (argv);
		pipex.outfile = open(argv[argc - 1],O_WRONLY | O_CREAT | O_APPEND,0644);
		if (pipex.outfile == -1)
			ft_msg_error("Error\n Wrong outfile");
	}
	if (ft_strncmp(argv[1],"here_doc",9) != 0)
	{
		pipex.here_doc = 2; //argv[2]
		pipex.infile = open (argv[1],O_RDONLY);
		if (pipex.infile == -1)
			ft_msg_error("Error\n Wrong infile");
		pipex.outfile = open (argv[argc - 1],O_RDWR | O_CREAT | O_TRUNC ,0644);
		if (pipex.outfile == -1)
			ft_msg_error("Error\n Wrong outfile");
		if (dup2(pipex.infile, STDIN_FILENO) == -1)
			ft_msg_error("Error\n Wrong dup to infile");

	}
	while (pipex.here_doc < argc - 2) // outfile + last cmd
			multi_pipe (argv[pipex.here_doc++],&pipex,envp);
	if (dup2(pipex.outfile,STDOUT_FILENO)==-1)
		ft_msg_error("Error\n Wrong dup to outfile");
	execute_cmd(argv[argc -2],&pipex,envp);
	return (0);

}
