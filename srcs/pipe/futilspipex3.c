/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   futilspipex3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:23:56 by rmonacho          #+#    #+#             */
/*   Updated: 2022/05/10 14:50:18 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"
#include <termios.h>
#include "../../incs/parsing.h"

void	ft_seterrnopath(t_mini *mini, char *cmd)
{
	int		i;
	char	temp[1];

	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
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
