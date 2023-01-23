/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:18:57 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/23 03:28:18 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void here_doc (char *limiter)
{
	int temp_file;
	char *line;

	temp_file = open ("here_doc_temp",O_WRONLY | O_CREAT | O_TRUNC,0644);
	if (temp_file == -1)
		ft_msg_error("Error\n Wrong temp_heredoc");
	while (1)
	{
		write (1,"heredoc>",9);
		line = get_next_line (STDIN_FILENO);
		if (!line)
			ft_msg_error("Error\n");
		if (ft_strncmp(limiter,line,ft_strlen(limiter)) == 0)
			break;
		if(write (temp_file,line,ft_strlen(line))==-1)
			ft_msg_error("Error\n Wrong write");
		free(line);
	}
	free (line);
	close (temp_file);
}

