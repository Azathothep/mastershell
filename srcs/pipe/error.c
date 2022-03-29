/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:31:26 by rmonacho          #+#    #+#             */
/*   Updated: 2022/03/29 12:35:15 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_close(t_mini *mini, int i)
{
	if (i != 0)
	{
		if (close(mini->pipex->tube[2 * i - 2]) == -1
			|| close(mini->pipex->tube[2 * i - 1]) == -1)
			return (ft_seterrno(11));
	}
	if (mini->pipex->infile != -1)
	{
		if (close(mini->pipex->infile) == -1)
			return (ft_seterrno(11));
	}
	if (mini->pipex->outfile != -1)
	{
		if (close(mini->pipex->outfile) == -1)
			return (ft_seterrno(11));
	}
	if (i == mini->nbc - 1)
	{
		if (close(mini->pipex->tube[2 * i]) == -1
			|| close(mini->pipex->tube[2 * i + 1]) == -1)
			return (ft_seterrno(11));
	}
	return (0);
}

void	ft_seterrout(void)
{
	int	i;

	i = errno;
	if (i == EACCES)
		errno = 8;
	if (i == EISDIR)
		errno = 9;
	else
		errno = 10;
}

int	ft_seterrin(int j)
{
	int	i;

	i = errno;
	if (i == EACCES)
		errno = 5;
	if (i == ENOENT)
		errno = 4;
	if (i == EISDIR)
		errno = 6;
	else
		errno = 7;
	return (j);
}

int	ft_seterrno(int i)
{
	errno = i;
	return (-1);
}

int	ft_error(int i, t_mini *mini, int j)
{
	(void)mini;
	(void)i;
	(void)j;
	printf("errno = %d\n", errno);
	return (-1);
}
