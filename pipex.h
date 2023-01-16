/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:14:54 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/15 23:11:02 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include<unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
typedef struct s_pipex
{
	int infile;
	int outfile;
	int end[2]; //end[1] :write end //end[0] : read end
	pid_t pid1;
	pid_t pid2;
	char *path;
	char **my_cmd_path;
	char **cmd_args;
	char *cmd;

}		t_pipex;

void ft_msg_error (char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
#endif
