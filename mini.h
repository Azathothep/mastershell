/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:02:34 by rmonacho          #+#    #+#             */
/*   Updated: 2022/03/14 16:54:49 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*Explications sur la structure et sur le format des 
donnees necessaires en sortie de parsing*/

typedef struct mini
{
	char	***commands; /* La table de commande qui regroupe dans chaque tableau
	 					les commandes entre les pipes et leurs arguments. Exemple : tab[0] = [ls , -l, -a], tab[1] = [cd, ..]*/
						 
	t_file	*infile; /* Une structure qui est compose d'un char * (represente la nouvelle entree, filename ou texte pour le <<)
						et un bouleen (definit si la redirection d'entree est un <(0) ou un <<(1)) */

	t_file	*outfile; /* Idem mais pour l'outfile avec le booleen qui donne l'info sur <(0) ou <<(1) */

	t_pipe	*pipe;	/* Structure qui definit la redirection de fichier qui a ete demandee. Composee de deux char *, infile et outfile et d'un boolean pour le type de chevron*/
					/* Utilise notemment pour rediriger la sortie d'erreur et si ca se trouve unique;ent pour ca */

	char	**cmdenv; /* table qui comporte toutes les nouvelles definitions de variables d'environnements a mettre en place (quand l'utilisateur tape mavariable="lol")
						Ne pas mettre a l'interieur les commandes export unset et env, elles sont a ;ettre dans commands*/
	t_list	*envp;	/* Cet element correspond a l'environnement que tu recuperes dans le main mais convertit en t_list pour permettre de le manier plus facilement*/ 
					/* Dans l'idee tu peux me le passer en char **envp et je ferai le changement en t_list de mon cote*/

	//Quelque chose pour les signaux ? Uniquement pour le Ctrl + C les autres n'envoient pas de signaux mais je n'y connais rien gduwqgduq
};
