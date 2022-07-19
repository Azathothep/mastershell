/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:28:44 by rmonacho          #+#    #+#             */
/*   Updated: 2022/07/19 15:48:44 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/pipe.h"

char	*ft_getfiles(int i, t_mini *mini, int j)
{
	int		k;
	t_list	*temp;

	k = 0;
	if (errno >= 8)
	{
		temp = mini->outfile[i].files;
		while (k < j)
		{
			temp = temp->next;
			k++;
		}
		return (temp->content);
	}
	else
	{
		temp = mini->infile[i].files;
		while (k < j)
		{
			temp = temp->next;
			k++;
		}
		return (temp->content);
	}
}

int	ft_error5(t_mini *mini, int i, int j)
{
	char	*temp;

	if (errno == 3)
	{
		write(mini->pipex->errfile, "mishell : ", 10);
		write(mini->pipex->errfile, mini->commands[i][0],
			ft_strlen(mini->commands[i][0]));
		write(mini->pipex->errfile, ": Command not found\n", 20);
		g_exitstatus = 127;
	}
	if (errno == 4)
	{
		temp = ft_getfiles(i, mini, j);
		write(mini->pipex->errfile, "mishell : ", 10);
		write(mini->pipex->errfile, temp, ft_strlen(temp));
		write(mini->pipex->errfile, " : No such file or directory\n", 29);
	}
	return (0);
}

int	ft_error4(int i, t_mini *mini)
{
	if (errno == 28)
	{
		write(mini->pipex->errfile, "mishell : ", 10);
		write(mini->pipex->errfile, mini->commands[i][0],
			ft_strlen(mini->commands[i][0]));
		write(mini->pipex->errfile, ": No such file or directory\n", 29);
	}
	if (errno == 29)
	{
		write(mini->pipex->errfile, "mishell : ", 10);
		write(mini->pipex->errfile, mini->commands[i][0],
			ft_strlen(mini->commands[i][0]));
		write(mini->pipex->errfile, ": Is a directory\n", 18);
	}
	if (errno == 30)
		write(mini->pipex->errfile,
			"mishell : No such file or directory\n", 36);
	if (errno == 31)
		write(mini->pipex->errfile,
			"mishell : No such file or directory\n", 36);
	if (errno == 32)
		write(mini->pipex->errfile,
			"mishell : No such file or directory\n", 36);
	return (0);
}

int	ft_error3(int i, t_mini *mini, int j)
{
	char	*temp;

	if (errno == 8)
	{
		temp = ft_getfiles(i, mini, j);
		write(mini->pipex->errfile, "mishell : ", 10);
		write(mini->pipex->errfile, temp, ft_strlen(temp));
		write(mini->pipex->errfile, " : Permission denied\n", 21);
	}
	if (errno == 9)
	{
		temp = ft_getfiles(i, mini, j);
		write(mini->pipex->errfile, "mishell : ", 10);
		write(mini->pipex->errfile, temp, ft_strlen(temp));
		write(mini->pipex->errfile, " : Is a directory\n", 18);
	}
	if (errno == 10)
		write(mini->pipex->errfile, "mishell : Open error outfile\n", 29);
	if (errno == 11)
	{
		write(mini->pipex->errfile,
			"mishell : dup, fork, execve or close error\n", 43);
	}
	ft_error4(i, mini);
	return (0);
}

int	ft_error2(int i, t_mini *mini, int j)
{
	char	*temp;

	if (errno == 5)
	{
		temp = ft_getfiles(i, mini, j);
		write(mini->pipex->errfile, "mishell : ", 10);
		write(mini->pipex->errfile, temp, ft_strlen(temp));
		write(mini->pipex->errfile, " : Permission denied\n", 21);
	}
	if (errno == 6)
	{
		temp = ft_getfiles(i, mini, j);
		write(mini->pipex->errfile, "mishell : ", 10);
		write(mini->pipex->errfile, temp, ft_strlen(temp));
		write(mini->pipex->errfile, " : Is a directory\n", 18);
	}
	if (errno == 7)
		write(mini->pipex->errfile, "mishell : Open error infile\n", 28);
	if (errno >= 8)
		ft_error3(i, mini, j);
	return (0);
}
