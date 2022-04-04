/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:06:17 by rmonacho          #+#    #+#             */
/*   Updated: 2022/03/31 13:43:15 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "mini.h"

/* pipe.c */
int		ft_start_pipe(t_mini *mini);
	/* Fonction maitresse de la partie execution */
int		ft_pipex(t_mini *mini, int i, t_pipex *pipex);
	/* Fonction maitresse de la partie pipex */
int		ft_child(t_mini *mini, int mode, int i, t_pipex *pipex);
int		ft_child2(t_mini *mini, int mode, int i, t_pipex *pipex);

/* pipe2.c */
/* Fonctions d'execution des pipes */
int		ft_last_pipe(t_mini *mini, int i, t_pipex *pipex);
int		ft_last_pipe2(t_mini *mini, int i, t_pipex *pipex);
int		ft_first_pipe(t_mini *mini, t_pipex *pipex);
int		ft_first_pipe2(t_mini *mini, t_pipex *pipex);

/* pipehere.c */
/* Fonctions d'executions pour la prise en compte des pipes */
int		ft_nexthere(t_mini *mini, int i);
int		ft_pipehere(t_mini *mini, int i, t_pipex *p);
int		ft_child2h(t_mini *mini, int mode, int i, t_pipex *pipex);
int		ft_childh(t_mini *mini, int mode, int i, t_pipex *pipex);

/* pipehere2.c */
int		ft_first_pipe2h(t_mini *mini, t_pipex *pipex);
int		ft_first_pipeh(t_mini *mini, t_pipex *pipex);

/* initpipex */
int		ft_init_pipex(t_mini *mini, int i);
char	*ft_path(char *cmd, t_list *envpl);
char	**ft_initpath(int	*i, t_list *envpl);
int		ft_puthere(t_mini *mini, t_pipex *p, int i);

/* initpipex2.c */
int		ft_inittube(t_mini *mini, t_pipex *pipex);
int		ft_init_files(t_mini *mini, int i);
int		ft_init_files2(t_mini *mini, int i);
int		ft_searchin(t_inout *infile, int i);
int		ft_searchout(t_inout *outfile, int i);

/* initpipex3.c */
char	*ft_joinpath(char **tab, char *cmd, int i);
int		ft_init_start(t_mini *mini);

/* error.c */
int		ft_error(int i, t_mini *mini, int j);
int		ft_seterrno(int i);
int		ft_seterrin(int j);
void	ft_seterrout(void);
int		ft_close(t_mini *mini, int i);

/* builtin.c */
int		ft_pwd(t_mini *mini, char **cmd, int j, t_pipex *pipex);
int		ft_cd(t_mini *mini, char **cmd);
int		ft_echo(char **cmd, t_pipex *pipex, int j);
int		ft_builtin(t_mini *mini, char **cmd, t_pipex *pipex, int i);
int		ft_isbuiltin(char **cmd);

/* builtin2.c */

/* ft_utils.c */
char	**ft_convert(t_list *envpl); /* Conversion de la liste env en char** */
int		ft_openout(t_inout *lfiles, int j);
	/* Ouverture des fichiers de sortie */
int		ft_openin(t_inout *lfiles, int j); /* Ouverture des fichiers d'entree */

/* debug.c */

void	ft_printlst(t_list *list);

# define R	O_RDWR
# define C	O_CREAT
# define T	O_TRUNC
# define I	S_IRUSR
# define W	S_IWUSR
# define G	S_IRGRP
# define H	S_IROTH
# define P	O_APPEND

#endif