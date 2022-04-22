/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:25:08 by rmonacho          #+#    #+#             */
/*   Updated: 2022/04/21 16:23:49 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_errorcd(t_mini *mini, int mode, char *cmd)
{
	if (mode == 1)
	{
		write(mini->pipex->errfile, "cd : ", 6);
		write (mini->pipex->errfile, cmd, ft_strlen(cmd));
		write(mini->pipex->errfile, ": No such file or directory\n", 29);
		errno = 16;
	}
	if (mode == 2)
	{
		write(mini->pipex->errfile, "cd : OLDPWD not set\n", 21);
		errno = 18;
	}
	return (-1);
}

int	ft_fill(t_mini *mini, char *cmd, char **path)
{
	t_list	*temp;

	temp = mini->envpl;
	if (cmd[0] == '-')
	{
		if (cmd[1] != '\0')
			return (ft_errorcd(mini, 1, cmd));
		while (temp != NULL)
		{
			if (ft_strncmp(temp->content, "OLDPWD", 6) == 0)
			{
				printf("lol\n");
				*path = ft_strdup(temp->content);
				if (*path == NULL)
					return (ft_seterrno(1));
				return (0);
			}
			temp = temp->next;
		}
		return (ft_errorcd(mini, 2, cmd));
	}
	*path = ft_strdup(cmd);
	if (*path == NULL)
		return (ft_seterrno(1));
	return (0);
}

char	*ft_ishome(t_mini *mini, char *cmd)
{
	t_list	*temp;

	temp = mini->envpl;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->content, "HOME=", 5) == 0)
			return (ft_strdup(temp->content + 5));
		temp = temp->next;
	}
	if ((cmd[0] == '-' && cmd[1] == '-') || (cmd[0] == '~'))
		return (ft_strdup("/Users/rmonacho"));
	return (NULL);
}
