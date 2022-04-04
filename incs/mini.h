/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:02:34 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/01 14:27:00 by marvin           ###   ########.fr       */
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
	t_list	**heredocs; //tableau de listes chaînées contenant les heredocs
						//heredocs[0] renvois la première liste des heredocs de la première commande
						//heredocs[0]->next renvois le 2e heredoc de la première commande etc...
						//(pour récupérer le char * de la liste, utiliser get_token(heredocs[i]));
	char	**cmdenv;
	t_list	*envpl;
	int		nbc;
	t_pipex	*pipex;
	char	**envp;
	int		exit_status;
}	t_mini;
#endif