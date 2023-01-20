/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:14:54 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/20 01:13:23 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include<unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
typedef struct s_pipex
{
	int infile;
	int outfile;
	int end[2]; //end[1] :write end //end[0] : read end
	pid_t pid1;
	pid_t pid2;
	char *paths;
	char **cmd_paths;
	char **cmd1_args;
	char **cmd2_args;
	char *cmd;

}		t_pipex;

void	ft_msg_error (char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*get_cmd_path(char **path,char *command);
void 	get_path(t_pipex *pipex,char **envp);
void child1 (t_pipex pipex,char **argv,char **envp);
void child2 (t_pipex pipex,char **argv,char **envp);
void ft_close (t_pipex *pipex);
void free_array(char **array);
#endif
