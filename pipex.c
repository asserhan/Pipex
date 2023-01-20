/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:03:24 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/20 02:36:38 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void 	get_path(t_pipex *pipex,char **envp)
{
	char *temp;
	int i;
	i = -1;
	while (ft_strncmp("PATH",*envp,4)!=0)
			envp++;
	pipex->paths = *envp + 5;
	pipex->cmd_paths = ft_split(pipex->paths,':');
	if (!pipex->cmd_paths)
		ft_msg_error("Error\n");
	while (pipex->cmd_paths[++i])
	{
		temp = pipex->cmd_paths[i];
		pipex->cmd_paths[i]= ft_strjoin(temp,"/");
		// if (!pipex->cmd_paths[i])
		// 	ft_msg_error("Error\n");
		free (temp);
	}
}
void ft_close (t_pipex *pipex)
{
	if (close(pipex->end[1]) == -1)
		ft_msg_error ("Error\n Wrong close of pipe end[1]");
	if (close(pipex->end[0]) == -1)
		ft_msg_error ("Error\n Wrong close of pipe end[0]");

}

int main (int argc,char **argv ,char **envp)
{

	t_pipex pipex;
	//int i=0;

	if (argc != 5)
		ft_msg_error("Error\n Wrong Argument");
	pipex.infile = open (argv[1],O_RDONLY);
	if(pipex.infile == -1 || access (argv[1],W_OK) == -1)
		ft_msg_error("Error\n Wrong infile");
	pipex.outfile =open(argv[4],O_RDWR | O_CREAT | O_TRUNC , 0644);
	if(pipex.outfile == -1 )
		ft_msg_error("Error\n Wrong outfile");
	if (pipe(pipex.end) == -1)
		ft_msg_error ("Error with pipe\n ");
	get_path(&pipex,envp);
	pipex.cmd1_args =ft_split(argv[2],' ');
	pipex.cmd2_args =ft_split(argv[3],' ');

	// i =0;
	// while (i < 1)
	// {
	// 	printf("%s\n",pipex.cmd1_args[i]);
	// 	printf("%s\n",pipex.cmd2_args[i]);
	// 	i++;
	// }
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		ft_msg_error("Error \n  No child process is created");
	if (pipex.pid1 == 0) //child process 1
		child1(pipex,envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		ft_msg_error("Error \n  No child process is created");
	if (pipex.pid2 == 0) //child process 2
		child2(pipex,envp);
	ft_close(&pipex);
	waitpid(pipex.pid1,NULL,0);
	waitpid(pipex.pid2,NULL,0);
	free_array(pipex.cmd_paths);
	if (close(pipex.infile) == -1)
		ft_msg_error("Error\n Wrong close infile");
	if (close(pipex.outfile) == -1)
		ft_msg_error("Error\n Wrong close outfile");

	return (0);

}
