/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:51:21 by sbrochar          #+#    #+#             */
/*   Updated: 2025/10/27 18:57:35 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		pipe_fd[2];
	int		fd[2];
	char	**paths;
	char	**envp;
	char	*infile;
	char	*outfile;
	char	*cmd1;
	char	*cmd2;
	char	**final_cmd1;
	char	**final_cmd2;

}			t_pipex;

char		**get_paths(char **envp);
char		*ft_strchr(const char *str, int c);
char		*try_path(char *paths, char *cmd);
char		*check_path(char **paths, char *cmd);
char		*get_cmd_path(char *cmd, char **paths);
char		**parse_cmd(char *cmd);
char		**build_cmd(char *cmd, char **paths);
char		**ft_split(char const *str, char sep);
size_t		ft_strlen(const char *str);
char		*ft_substr(char const *str, unsigned int start, size_t len);
char		*ft_strcpy(char *restrict dest, const char *restrict src);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_strdup(const char *src);
char		*ft_strjoin(char const *str1, char const *str2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		run_cmd1(char *cmd, char *file_in, t_pipex *px);
void		free_argv(char **tabs);
void		run_cmd2(char *cmd, char *file_in, t_pipex *px);
int			run_child(t_pipex *px);
int			main(int argc, char **argv, char **envp);
void		free_struct(t_pipex *px);
void		clean_exit_child(t_pipex *px, char **argv, int code);

#endif