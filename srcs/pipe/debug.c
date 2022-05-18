/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:40:28 by rmonacho          #+#    #+#             */
/*   Updated: 2022/05/10 10:54:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

void	ft_printlst(t_list *list)
{
	printf("------------------\n");
	while (list != NULL)
	{
		//printf("- %s\n", list->content);
		list = list->next;
	}
}

void	ft_printpipe(int *tab, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		printf("%d ,", tab[j]);
		j++;
	}
	printf("\n");
}
