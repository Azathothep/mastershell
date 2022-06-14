/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:31:26 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/08 11:36:27 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/pipe.h"

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
		close(mini->pipex->tube[2 * i + 2]);
	}
	return (0);
}

int	ft_seterrout(int j)
{
	int	i;

	i = errno;
	if (i == 2)
		errno = 30;
	else if (i == EACCES)
		errno = 8;
	else if (i == EISDIR)
		errno = 9;
	else
		errno = 10;
	g_exitstatus = 1;
	return (j);
}

int	ft_seterrin(int j)
{
	int	i;

	i = errno;
	if (i == 2)
		errno = 31;
	else if (i == EACCES)
		errno = 5;
	else if (i == ENOENT)
		errno = 4;
	else if (i == EISDIR)
		errno = 6;
	else
		errno = 7;
	g_exitstatus = 1;
	return (j);
}

int	ft_seterrno(int i)
{
	errno = i;
	return (-1);
}

int	ft_error(int i, t_mini *mini, int j)
{
	char	*temp;

	if (errno == 1)
		write(mini->pipex->errfile, "mishell : Malloc error\n", 23);
	if (errno == 2)
	{
		write(mini->pipex->errfile, "mishell : ", 10);
		write(mini->pipex->errfile, mini->commands[i][0],
			ft_strlen(mini->commands[i][0]));
		write(mini->pipex->errfile, " no such file or directory\n", 27);
	}
	if (errno == 3)
	{
		write(mini->pipex->errfile, "mishell : ", 10);
		write(mini->pipex->errfile, mini->commands[i][0],
			ft_strlen(mini->commands[i][0]));
		write(mini->pipex->errfile, ": command not found\n", 20);
		g_exitstatus = 127;
	}
	if (errno == 4)
	{
		temp = ft_getfiles(i, mini, j);
		write(mini->pipex->errfile, "mishell : ", 10);
		write(mini->pipex->errfile, temp, ft_strlen(temp));
		write(mini->pipex->errfile, " : no such file or directory\n", 29);
	}
	if (errno >= 5)
		ft_error2(i, mini, j);
	errno = 0;
	return (-1);
}
