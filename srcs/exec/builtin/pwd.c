/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:04:28 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/08 10:23:19 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/pipe.h"

int	ft_errnopwd(t_mini *mini, char *buf)
{
	write(mini->pipex->errfile, "pwd : An error occured\n", 23);
	errno = 23;
	free(buf);
	ft_setexit(1, 0);
	return (-1);
}

int	ft_pwd(t_mini *mini, t_pipex *pipex)
{
	int		i;
	char	*name;
	char	*buf;

	i = 0;
	buf = malloc(sizeof(char) * (PATH_MAX + 1));
	if (buf == NULL)
		return (ft_seterrno(1));
	while (i <= PATH_MAX)
	{
		buf[i] = '\0';
		i++;
	}
	if (pipex->outfile == -1)
		pipex->outfile = 1;
	name = getcwd(buf, PATH_MAX);
	if (name == NULL)
		return (ft_errnopwd(mini, buf));
	write(pipex->outfile, name,
		ft_strlen(name));
	write(pipex->outfile, "\n", 1);
	free(buf);
	ft_setexit(0, 0);
	return (0);
}
