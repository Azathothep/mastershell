/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:41:32 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/29 11:24:57 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

void	ft_freeenvin(char ***envp)
{
	int	i;

	i = 0;
	if (*envp != NULL)
	{
		while ((*envp)[i] != NULL)
		{
			free((*envp)[i]);
			i++;
		}
	}
	free(*envp);
}

void	ft_freecommands(char ***cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmds == NULL)
		return ;
	while (cmds[i] != NULL)
	{
		while (cmds[i][j] != NULL)
		{
			free(cmds[i][j]);
			j++;
		}
		free(cmds[i]);
		i++;
		j = 0;
	}
	free(cmds);
}
