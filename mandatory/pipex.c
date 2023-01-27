/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:03:24 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/27 03:25:51 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(t_pipex *pipex, char **argv)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1 || access (argv[1], W_OK) == -1)
		perror("Error\nWrong infile");
	pipex->outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		ft_msg_error("Error\nWrong outfile");
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		ft_msg_error("Error\nWrong Argument");
	open_files (&pipex, argv);
	if (pipex.infile < 0 || pipex.outfile < 0)
		exit(1);
	if (pipe(pipex.end) == -1)
		ft_msg_error ("Error with pipe\n ");
	get_path(&pipex, envp);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		ft_msg_error("Error \nNo child process is created");
	if (pipex.pid1 == 0)
		child1(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		ft_msg_error("Error\nNochild process is created");
	if (pipex.pid2 == 0)
		child2(pipex, argv, envp);
	ft_close(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}
