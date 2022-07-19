/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initpipex5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:22:32 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/28 11:31:41 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/pipe.h"

int	ft_startpath(char *cmd, char ***tab, int *i, t_list *envpl)
{
	if (cmd[0] == '\0')
	{
		ft_seterrno(3);
		return (-1);
	}
	if (access(cmd, X_OK) == 0 && ft_testdirectory(cmd) != -1)
		return (1);
	*i = 0;
	*tab = ft_initpath(i, envpl);
	if (*tab == NULL)
		return (-1);
	return (0);
}
