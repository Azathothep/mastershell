/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:02:34 by rmonacho          #+#    #+#             */
/*   Updated: 2022/03/15 12:49:57 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*Explications sur la structure et sur le format des 
donnees necessaires en sortie de parsing */

#include "lib.h"

typedef struct s_inout
{
	char	*name;
	int		pos;
	int		type;
}	t_inout;

typedef struct s_file
{
	char	*name;
	int		type;
}	t_file;


typedef struct s_pipex
{
	char	*cmd;
	int		*tube;
	int		infile;
	int		outfile;
	char	*path;
}	t_pipex;

typedef struct s_mini
{
	char	***commands; /* La table de commande qui regroupe dans chaque tableau
	 					les commandes entre les pipes et leurs arguments. Exemple : tab[0] = [ls, -l, -a], tab[1] = [cd, ..]*/
						 
	t_inout	*infile; /* Une structure qui est compose d'un char * (represente la nouvelle entree, filename ou texte pour le <<)
						et un bouleen (definit si la redirection d'entree est un <(0) ou un <<(1)) */

	t_inout	*outfile; /* Idem mais pour l'outfile avec le booleen qui donne l'info sur <(0) ou <<(1) */

	t_file	*errfile;	/* idem mais sortie d'erreur */

	char	**cmdenv; /* table qui comporte toutes les nouvelles definitions de variables d'environnements a mettre en place (quand l'utilisateur tape mavariable="lol")
						Ne pas mettre a l'interieur les commandes export unset et env, elles sont a mettre dans commands*/

	t_list	*envpl;	/* Cet element correspond a l'environnement que tu recuperes dans le main mais convertit en t_list pour permettre de le manier plus facilement*/ 
					/* Dans l'idee tu peux me le passer en char **envp et je ferai le changement en t_list de mon cote*/

	int		nbc; /* nombre de commande */

	t_pipex	*pipex; /* structure pipex */ 
	//Quelque chose pour les signaux ? Uniquement pour le Ctrl + C les autres n'envoient pas de signaux mais je n'y connais rien
}	t_mini;
