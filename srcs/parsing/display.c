/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:16:50 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/06/08 10:30:17 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/lib.h"
#include "../../incs/parsing.h"
#include "../../incs/mini.h"

void	print_lst(t_list **begin_lst)
{
	t_list	*lst;

	lst = *begin_lst;
	while (lst)
	{
		printf("token = %s$\n", (char *)lst->content);
		lst = lst->next;
	}
}

void	display_parsing(t_mini *mini)
{
	int		i;
	int		j;
	t_list	*lst;
	char	***commands;

	commands = mini->commands;
	i = -1;
	while (++i < mini->nbc)
	{
		j = -1;
		if (commands[i])
		{
		while (commands[i][++j])
			printf("%s ", commands[i][j]);
		printf("|| heredocs : ");
		lst = mini->heredocs[i];
		while (lst)
		{
			printf("%s ", get_token(lst));
			lst = lst->next;
		}
		printf("|| infiles : ");
		lst = mini->infile[i].files;
		while (lst)
		{
			printf("%s ", get_token(lst));
			lst = lst->next;
		}
		printf("|| outfiles : ");
		lst = mini->outfile[i].files;
		while (lst)
		{
			printf("%s ", get_token(lst));
			lst = lst->next;
		}
		printf("|| errfiles : ");
		lst = mini->errfile[i].files;
		while (lst)
		{
			printf("%s ", get_token(lst));
			lst = lst->next;
		}
		printf("\n");
		}
		
	}
}
