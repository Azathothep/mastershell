/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:50:41 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/21 11:49:10 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_env(t_mini *mini)
{
	t_list	*temp;

	temp = mini->envpl;
	if (mini->pipex->outfile == -1)
		mini->pipex->outfile = 1;
	while (temp != NULL)
	{
		if (ft_strchr(temp->content, '=') != NULL)
		{
			write(mini->pipex->outfile, temp->content,
				ft_strlen(temp->content));
			write(mini->pipex->outfile, "\n", 1);
		}
		temp = temp->next;
	}
	return (0);
}