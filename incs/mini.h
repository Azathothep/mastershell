/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:02:34 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/05 11:12:02 by rmonacho         ###   ########lyon.fr   */
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
	char	**cmdenv;
	t_list	*envpl;
	int		nbc;
	t_pipex	*pipex;
	char	**envp;
	int		exit_status;
	int		*pid;
}	t_mini;
#endif