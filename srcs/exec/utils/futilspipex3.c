/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   futilspipex3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:23:56 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/08 10:25:54 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/pipe.h"
#include <termios.h>
#include "../../../incs/parsing.h"

int	ft_eraseold(t_mini *mini)
{
	t_list	*temp;
	char	*cont;

	temp = mini->envpl;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->content, "OLDPWD=", 7) == 0
			|| ft_strncmp(temp->content, "OLDPWD", 7) == 0)
		{
			cont = ft_strdup("OLDPWD");
			if (cont == NULL)
				return (ft_seterrno(1));
			free(temp->content);
			temp->content = cont;
			return (0);
		}
		temp = temp->next;
	}
	return (0);
}

void	ft_seterrnopath(t_mini *mini, char *cmd)
{
	int		i;
	char	temp[1];

	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/')
		|| ft_strchr(cmd, '/') != NULL)
	{
		i = open(cmd, O_RDONLY);
		if (i < 0)
		{
			errno = 28;
			return ;
		}
		if (read(i, temp, 1) < 0)
		{
			errno = 29;
			return ;
		}
	}
	else
		errno = 3;
	mini->envp = mini->envp;
}

void	ft_freetabenv(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->envp == NULL)
		return ;
	while (mini->envp[i] != NULL)
	{
		free(mini->envp[i]);
		i++;
	}
	free(mini->envp);
}

void	ft_freelistenv(t_mini *mini)
{
	t_list	*temp;
	t_list	*temp2;

	temp = mini->envpl;
	if (mini->envpl == NULL)
		return ;
	while (temp != NULL)
	{
		temp2 = temp;
		free(temp->content);
		temp = temp->next;
		free(temp2);
	}
}

int	ft_freechar(char *name, int i)
{
	free(name);
	return (i);
}
