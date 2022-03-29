/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:40:28 by rmonacho          #+#    #+#             */
/*   Updated: 2022/03/29 12:24:08 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

void	ft_printlst(t_list *list)
{
	printf("------------------\n");
	while (list != NULL)
	{
		printf("- %s\n", list->content);
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
