/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:13:06 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/28 11:15:37 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/pipe.h"

void	ft_endcd(char *path, char *lastpath)
{
	ft_setexit(0, 0);
	free(path);
	free(lastpath);
}
