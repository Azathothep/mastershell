/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:41:32 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/08 10:23:53 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/pipe.h"

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

void	ft_closefour(t_mini *mini)
{
	close(mini->pipex->tube[0]);
	close(mini->pipex->tube[1]);
	close(mini->pipex->tube[2]);
	close(mini->pipex->tube[3]);
}

void	ft_initspace(int *i, t_mini *mini)
{
	*i = 0;
	errno = 0;
	ft_termios_ctl(mini);
}
