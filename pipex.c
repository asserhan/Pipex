/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:03:24 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/15 23:58:07 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void 	get_env_path(t_pipex *pipex,char **envp)
{
	while (ft_strncmp("PATH",*envp,4)!=0)
			envp++;
	pipex->path = *envp + 5;
	pipex->my_cmd_path = ft_split(pipex->path,':');
}

int main (int argc,char **argv ,char **envp)
{

	(void )argv;
	(void )argc;
	t_pipex pipex;
	int i=0;

	if (argc != 5)
		ft_msg_error("Error\n Wrong Argument");
	if (pipe(pipex.end) < 0)
		ft_msg_error ("Error with pipe\n ");
	get_env_path(&pipex,envp);
	pipex.pid1 = fork ();
	if (pipex.pid1 < 0)
		ft_msg_error("Error \n  No child process is created");
	if (pipex.pid1 == 0) //child process 1
	{

	}
	waitpid(pipex.pid1,NULL,0);

	return (0);

}
