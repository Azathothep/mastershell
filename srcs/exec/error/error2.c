/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:28:44 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/08 10:23:46 by rmonacho         ###   ########lyon.fr   */
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

int	ft_error4(int i, t_mini *mini)
{
	if (errno == 28)
	{
		write(mini->pipex->errfile, "mastershell : ", 14);
		write(mini->pipex->errfile, mini->commands[i][0],
			ft_strlen(mini->commands[i][0]));
		write(mini->pipex->errfile, ": no such file or directory\n", 29);
	}
	if (errno == 29)
	{
		write(mini->pipex->errfile, "mastershell : ", 14);
		write(mini->pipex->errfile, mini->commands[i][0],
			ft_strlen(mini->commands[i][0]));
		write(mini->pipex->errfile, ": is a directory\n", 18);
	}
	if (errno == 30)
		write(mini->pipex->errfile,
			"mastershell : No such file or directory\n", 41);
	if (errno == 31)
		write(mini->pipex->errfile,
			"mastershell : No such file or directory\n", 41);
	if (errno == 32)
		write(mini->pipex->errfile,
			"mastershell : No such file or directory\n", 41);
	return (0);
}

int	ft_error3(int i, t_mini *mini, int j)
{
	char	*temp;

	if (errno == 8)
	{
		temp = ft_getfiles(i, mini, j);
		write(mini->pipex->errfile, "mastershell : ", 14);
		write(mini->pipex->errfile, temp, ft_strlen(temp));
		write(mini->pipex->errfile, " : permission denied\n", 21);
	}
	if (errno == 9)
	{
		temp = ft_getfiles(i, mini, j);
		write(mini->pipex->errfile, "mastershell : ", 14);
		write(mini->pipex->errfile, temp, ft_strlen(temp));
		write(mini->pipex->errfile, " : is a directory\n", 18);
	}
	if (errno == 10)
		write(mini->pipex->errfile, "mastershell : open error outfile\n", 33);
	if (errno == 11)
	{
		write(mini->pipex->errfile,
			"mastershell : dup, fork, execve or close error\n", 47);
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
		write(mini->pipex->errfile, "mastershell : ", 14);
		write(mini->pipex->errfile, temp, ft_strlen(temp));
		write(mini->pipex->errfile, " : permission denied\n", 21);
	}
	if (errno == 6)
	{
		temp = ft_getfiles(i, mini, j);
		write(mini->pipex->errfile, "mastershell : ", 14);
		write(mini->pipex->errfile, temp, ft_strlen(temp));
		write(mini->pipex->errfile, " : is a directory\n", 18);
	}
	if (errno == 7)
		write(mini->pipex->errfile, "mastershell : open error infile\n", 32);
	if (errno >= 8)
		ft_error3(i, mini, j);
	return (0);
}
