/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 00:43:30 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/27 05:31:40 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		here_doc;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_arg;
	char	*cmd;
	int		end[2];
	pid_t	pid1;
	pid_t	pid2;
	int		cmd_nbr;
	int		end_nbr;
	int		*end_tab;

}			t_pipex;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*read_and_add(int fd, char *reserve);
char	*update_reserve(char **reserve, int i);
char	*extract(char **reserve);
void	ft_msg_error(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
void	here_doc(char **argv);
void	write_to_heredoc(int *end, char *limiter);
void	open_files(t_pipex *pipex, int argc, char **argv);
char	*get_cmd_path(char **path, char *command);
void	get_path(t_pipex *pipex, char **envp);
void	ft_close(t_pipex *pipex);
void	free_array(char **array);
void	execute_cmd(char *cmd, t_pipex *pipex, char **envp);
void	multi_pipe(char *cmd, t_pipex *pipex, char **envp);
#endif
