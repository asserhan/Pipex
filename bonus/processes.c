/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 01:54:56 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/23 23:05:54 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		if (!pipex->cmd_paths[i])
			ft_msg_error("Error\n");
		free (temp);
	}
}
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


