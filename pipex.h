/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:14:54 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/15 11:32:37 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include<unistd.h>
typedef struct s_pipex
{
	char *path;
	char **my_cmd_path;
	char **cmd_args;
	char *cmd;

}		t_pipex;
#endif
