/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initpipex2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:10:37 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/08 10:09:12 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_errfiles(t_mini *mini, int i)
{
	char	*name;
	int		j;

	if (mini->errfile[i].files == NULL)
		mini->pipex->errfile = 2;
	else
	{
		j = ft_openerr(mini->errfile, i);
		if (j != 0)
			return (ft_seterr(mini, j));
		name = ft_lstlast(mini->errfile[i].files)->content;
		if (*(int *)(ft_lstlast(mini->errfile->types)->content) == 0)
		{
			mini->pipex->errfile = open(name, O_RDWR | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
		else
			mini->pipex->errfile = open(name, R | C | P, I | W | G | H);
		if (mini->pipex->errfile < 0)
		{
			ft_seterrfiles(0);
			return (ft_seterr(mini, -1));
		}
	}
	return (0);
}

int	ft_init_files2(t_mini *mini, int i)
{
	char	*name;
	int		j;

	if (mini->outfile[i].files == NULL)
		mini->pipex->outfile = -1;
	else
	{
		j = ft_openout(mini->outfile, i);
		if (j != 0)
			return (j);
		name = ft_lstlast(mini->outfile[i].files)->content;
		if (*(int *)(ft_lstlast(mini->outfile[i].types)->content) == 0)
		{
			mini->pipex->outfile = open(name, O_RDWR | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
		else
			mini->pipex->outfile = open(name, R | C | P, I | W | G | H);
		if (mini->pipex->outfile < 0)
		{
			ft_seterrout(0);
			return (-1);
		}
	}
	return (0);
}

int	ft_init_files(t_mini *mini, int i)
{
	int		j;
	char	test[1];

	j = ft_errfiles(mini, i);
	if (j != 0)
		return (j);
	if (mini->infile[i].files == NULL)
		mini->pipex->infile = -1;
	else
	{
		j = ft_openin(mini->infile, i);
		if (j != 0)
			return (j);
		mini->pipex->infile = open(ft_lstlast(mini->infile[i].files)->content,
				O_RDONLY);
		if (mini->pipex->infile < 0)
			return (ft_seterrin(-1));
		if (read(mini->pipex->infile, test, 1) < 0)
			return (ft_seterrin(-1));
	}
	j = ft_init_files2(mini, i);
	if (j != 0)
		return (j);
	return (0);
}

int	ft_inittube(t_mini *mini, t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->tube = malloc(sizeof(int) * ((mini->nbc + 1) * 2));
	if (pipex->tube == NULL)
		return (ft_seterrno(1));
	while (i <= mini->nbc)
	{
		if (pipe(pipex->tube + (2 * i)) == -1)
			return (ft_seterrno(1));
		i++;
	}
	return (0);
}
