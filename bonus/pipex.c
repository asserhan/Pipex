/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 05:15:50 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/27 05:31:20 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_msg_error(char *str)
{
	perror (str);
	exit (1);
}

void	open_files(t_pipex *pipex, int argc, char **argv)
{
	if (pipex->here_doc == 3)
	{
		pipex->outfile = open(argv[argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (pipex->outfile == -1)
			ft_msg_error("Error\nWrong outfile");
	}
	if (pipex->here_doc == 2)
	{
		pipex->outfile = open (argv[argc - 1],
				O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (pipex->outfile == -1)
			ft_msg_error("Error\n Wrong outfile");
		pipex->infile = open (argv[1], O_RDONLY);
		if (pipex->infile == -1)
			ft_msg_error("Error\n Wrong infile");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		ft_msg_error("Error\nWrong argument");
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		pipex.here_doc = 3;
		here_doc (argv);
		open_files(&pipex, argc, argv);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) != 0)
	{
		pipex.here_doc = 2;
		open_files(&pipex, argc, argv);
		if (dup2(pipex.infile, STDIN_FILENO) == -1)
			ft_msg_error("Error\n Wrong dup to infile");
	}
	while (pipex.here_doc < argc - 2)
		multi_pipe(argv[pipex.here_doc++], &pipex, envp);
	if (dup2(pipex.outfile, STDOUT_FILENO) == -1)
		ft_msg_error("Error\n Wrong dup to outfile");
	execute_cmd(argv[argc -2], &pipex, envp);
	return (0);
}
