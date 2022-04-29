/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:15:35 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/29 12:02:23 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

void	ft_freeenvp(char ***envp, t_list **envpl)
{
	int	i;

	i = 0;
	if (*envpl != NULL)
		ft_lstclear(envpl, free);
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

void	ft_freepipex(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->pipex != NULL)
	{
		free(mini->pipex->tube);
		// while (mini->pipex->cmd[i] != NULL)
		// {
		// 	free(mini->pipex->cmd[i]);
		// 	i++;
		// }
		//free(mini->pipex->cmd);
		free(mini->pipex->path);
	}
	free(mini->pipex);
}

int	ft_freeall(t_mini *mini)
{
	mini += 0;
	// free(mini->pid);
	// ft_freepipex(mini);
	// ft_freeenvp(&(mini->envp), &(mini->envpl));
	return (0);
}
