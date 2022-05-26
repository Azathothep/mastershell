/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:02:34 by rmonacho          #+#    #+#             */
/*   Updated: 2022/05/26 14:18:46 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Explications sur la structure et sur le format des 
donnees necessaires en sortie de parsing */

#ifndef MINI_H
# define MINI_H
# include "lib.h"

/* Structure servant au stockage des fichiers d'entrees,
sorties*/
typedef struct s_inout
{
	int		type;
	t_list	*types;
	t_list	*files;
}	t_inout;

/* Structure servant au stockage des fichiers d'erreurs*/
typedef struct s_file
{
	char	*name;
	int		type;
}	t_file;

/*Structure servant au stockage d'informations pour les pipes*/
typedef struct s_pipex
{
	char	**cmd;
	int		*tube;
	int		infile;
	int		outfile;
	int		errfile;
	char	*path;
}	t_pipex;

/* Structure globale du minishell*/
typedef struct s_mini
{
	char	***commands;
	t_inout	*infile;
	t_inout	*outfile;
	t_inout	*errfile;
	t_list	**heredocs;
	int		*infhere;
	t_list	*envpl;
	int		nbc;
	t_pipex	*pipex;
	char	**envp;
	int		exit_status;
	int		*pid;
	struct termios	termios_save;
}	t_mini;

void	ft_termios_ctl(t_mini *mini);
void	ft_termios_noctl(t_mini *mini);
void	ft_set_termios_save(t_mini *mini);

int	exitstatus;

#endif