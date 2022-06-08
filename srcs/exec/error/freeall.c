/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:15:35 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/08 10:23:50 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/pipe.h"

void	ft_freeenvp(char **envp, t_list *envpl)
{
	int	i;

	i = 0;
	if (envpl != NULL)
		ft_lstclear(&envpl, free);
	if (envp != NULL)
	{
		while ((envp)[i] != NULL)
		{
			free((envp)[i]);
			i++;
		}
	}
	free(envp);
}

void	ft_freepipex(t_mini *mini)
{
	if (mini->pipex != NULL)
	{
		free(mini->pipex->tube);
		free(mini->pipex->path);
	}
	free(mini->pipex);
}
