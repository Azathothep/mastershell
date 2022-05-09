/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:06:17 by rmonacho          #+#    #+#             */
/*   Updated: 2022/05/09 14:01:25 by rmonacho         ###   ########lyon.fr   */
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
t_list	*ft_convlist(char **envp);

/* f_utilspipex futilspipex2 futilspipehere */
void	ft_puthere2(t_mini *mini, t_list **t, int i, t_pipex *p);
void	ft_waitstart(t_mini *mini);
int		ft_startinit(t_mini *mini, int *i);
int		ft_pipe2(t_mini *mini, int i, t_pipex *p, int *j);
int		ft_endpipe(t_mini *mini, int i, t_pipex *p);
int		ft_initpipestart(t_mini *mini, int i, int *j);
int		ft_utilsfirstpipe(t_mini *mini, t_pipex *pipex);
int		ft_utilspipehere(t_mini *mini, t_pipex *p, int i, int *j);
int		ft_utils2pipehere(t_mini *mini, t_pipex *pipex);

/* error.c */
int		ft_error(int i, t_mini *mini, int j);
int		ft_seterrno(int i);
int		ft_seterrin(int j);
void	ft_seterrout(void);
int		ft_close(t_mini *mini, int i);
int		ft_error2(int i, t_mini *mini, int j);
char	*ft_getfiles(int i, t_mini *mini, int j);

/* builtin.c */
int		ft_builtin(t_mini *mini, char **cmd, t_pipex *pipex);
int		ft_isbuiltin(char **cmd);
int		ft_builtinpipe(t_mini *mini, char **cmd, t_pipex *pipex, int i);
int		ft_builtinpipehere(t_mini *mini, char **cmd, t_pipex *pipex);

/* pwd.c */
int		ft_pwd(t_mini *mini, t_pipex *pipex);

/* unset.c */
int		ft_unset(t_mini *mini, char **cmd, t_pipex *pipex);

/* export.c */
char	*ft_fullname(t_mini *mini, char *cmd);
char	ft_parseexp(char *cmd);
int		ft_isin(t_mini *mini, char *cmd);
int		ft_readd(t_mini *mini, char *cmd);
int		ft_checkequal(char *cmd);
int		ft_export(t_mini *mini, char **cmd, t_pipex *pipex);

/* exit.c */
int		ft_exit(t_mini *mini, char **cmd, int n);

/* env.c */
int		ft_env(t_mini *mini);

/* echo.c */
int		ft_echo(char **cmd, t_pipex *pipex);

/* cd.c */
int		ft_cd(t_mini *mini, char **cmd);
char	*ft_ishome(t_mini *mini, char *cmd);
int		ft_fill(t_mini *mini, char *cmd, char **path);
int		ft_errorcd(t_mini *mini, int mode, char *cmd);
int		ft_cd2(t_mini *mini, char **path, char **cmd, char **lastpath);
char	*ft_getpwd(void);
int		ft_oldpwd(t_mini *mini, char *lastpath);

/* ft_utils.c */
char	**ft_convert(t_list *envpl); /* Conversion de la liste env en char** */
char	**ft_convert2(char **envp);
int		ft_openout(t_inout *lfiles, int j);
void	status_child(t_mini *mini, int pid);
int		ft_testdirectory(char *cmd);

	/* Ouverture des fichiers de sortie */
int		ft_openin(t_inout *lfiles, int j); /* Ouverture des fichiers d'entree */
int		ft_openerr(t_inout *lfiles, int j);
void	ft_seterrfiles(void);
int		ft_seterr(t_mini *mini, int i);

/* freeall */

int		ft_freeall(t_mini *mini);
void	ft_freecommands(char ***cmds);
void	ft_freeenvin(char ***envp);
void	ft_freeenvp(char ***envp, t_list **envpl);
void	ft_freepipex(t_mini *mini);

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
