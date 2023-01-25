/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 05:16:08 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/25 01:11:39 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "pipex_bonus.h"

void	here_doc (char **argv)
{
	int		end[2];
	int		pid;

	if (pipe(end) == -1)
		ft_msg_error ("Error with pipe\n ");
	pid = fork();
	if (pid == -1)
		ft_msg_error("Error \n  No child process is created");
	if (pid == 0)
		write_to_heredoc(end, argv[2]);
	else
	{
		close(end[1]);
		if (dup2(end[0], STDIN_FILENO) == -1)
			ft_msg_error ("Error\n Wrong dup to pipe end[0]");
		close(end[0]);
		waitpid(pid, NULL, 0);
	}
}
void write_to_heredoc (int *end,char *limiter)
{
	char *line;
	if (close(end[0]) == -1)
		ft_msg_error ("Error\n Wrong close of pipe end[0]");
	while (1)
	{
		write (1,"heredoc>",9);
		line = get_next_line (STDIN_FILENO);
		if (!line)
			ft_msg_error("Error\n");
		if (ft_strncmp(limiter, line,ft_strlen(limiter)) == 0)
		{
			//free(line);
			close(end[1]);
			exit(1);
		}
		if (write(end[1], line, ft_strlen(line)) == -1)
			ft_msg_error("Error\n Wrong write");
		free(line);
	}
	free(line);
	if (close(end[1]) == -1)
		ft_msg_error ("Error\n Wrong close of pipe end[1]");
}

