/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:02:10 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/23 07:56:12 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void ft_msg_error (char *str)
{
	perror (str);
	exit (1);
}
void open_files (int argc,char **argv,t_pipex *pipex)
{
	if (pipex->here_doc == 3)
	{
		here_doc(argv[2]);
		pipex->infile = open ("here_doc_temp",O_RDONLY);
		if (pipex->infile == -1)
			ft_msg_error("Error\n Wrong infile");
		pipex->outfile = open(argv[argc - 1],O_WRONLY | O_CREAT | O_APPEND,0644);
		if (pipex->outfile == -1)
			ft_msg_error("Error\n Wrong outfile");
	}
	else
	{
		pipex->infile = open (argv[1],O_RDONLY);
		if (pipex->infile == -1)
			ft_msg_error("Error\n Wrong infile");
		pipex->outfile = open (argv[argc - 1],O_RDWR | O_CREAT | O_TRUNC ,0644);
		if (pipex->outfile == -1)
			ft_msg_error("Error\n Wrong outfile");

	}
}
void ft_creat_pipe (t_pipex *pipex)
{

}
int main(int argc,char **argv,char **envp)
{

	t_pipex pipex;
	(void)envp;

	if (argc < 5 )
		ft_msg_error("Error\n Wrong argument");
	if (argc == 6 && ft_strncmp(argv[1],"here_doc",9) == 0)
		pipex.here_doc = 3; //argv[3]
	if (argc > 5 &&  ft_strncmp(argv[1],"here_doc",9) != 0)
		pipex.here_doc = 2; //argv[2]
	open_files(argc,argv,&pipex);
	while (pipex.here_doc < argc - 2)
	{
		

	}
	// 2 (outfile + the last cmd)
	// pipex.cmd_nbr = argc - 3 - pipex.boolean;
	// pipex.end_nbr = 2 * (pipex.cmd_nbr - 1);
	// pipex.end_tab = (int *)malloc (sizeof(int) * pipex.end_nbr);
	// if (!pipex.end_tab)
	// 	ft_msg_error("Error\n malloc");
	// get_path(&pipex,envp);
	// ft_creat_pipe(&pipex)
	// if (pipe(pipex.end_tab) == -1)
	// 	ft_msg_error ("Error with pipe\n ");
	// pipex.cmd1_args =ft_split(argv[3],' ');
	// pipex.cmd2_args =ft_split(argv[4],' ');
	// pipex.pid1 = fork();
	// if (pipex.pid1 == -1)
	// 	ft_msg_error("Error \n No child process is created");
	// if (pipex.pid1 == 0)
	// 	child1(pipex,envp);
	// 	pipex.pid2 = fork();
	// if (pipex.pid2 == -1)
	// 	ft_msg_error("Error \n  No child process is created");
	// if (pipex.pid2 == 0) //child process 2
	// 	child2(pipex,envp);
	// ft_close(&pipex);
	// waitpid(pipex.pid1,NULL,0);
	// waitpid(pipex.pid2,NULL,0);
	// free_array(pipex.cmd_paths);
	// free_array (pipex.cmd1_args);
	// free_array(pipex.cmd2_args);
	return (0);

}
