/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevrons_utils.c                                        :+:      :+:    :*/
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:40:00 by marvin            #+#    #+#             */
/*   Updated: 2022/04/01 14:40:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/parsing.h"
#include "../../../incs/mini.h"
#include "../../../incs/lib.h"

int	format_ok(char const *filename)
{
	if (!filename || ft_inbase(filename[0], "!#&();<>|"))
		return (0);
	return (1);
}
