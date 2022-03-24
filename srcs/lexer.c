/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:35:09 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/24 13:04:24 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static int	init_chevrons(t_mini *mini)
{
	mini->heredocs = init_heredocs(mini->nbc);
	mini->infile = malloc(sizeof(t_inout) * (mini->nbc + 1));
	mini->infile = malloc(sizeof(t_inout) * (mini->nbc + 1));
	if (!mini->heredocs || !mini->infile || !mini->infile)
		return (0);
	return (1);
}

t_list	*lexer(char *buffer, t_mini *mini)
{
	t_list	*begin_lexicon;

	begin_lexicon = tokenize(buffer);
	if (!begin_lexicon)
		return (NULL);
	mini->nbc = get_cmdnb(begin_lexicon);
	if (!init_chevrons(mini))
	{
		ft_lstclear(&begin_lexicon, &lst_del);
		return (NULL);
	}
	process_chevrons(&begin_lexicon, mini);
	interpreter(&begin_lexicon, mini->exit_status);
	if (!begin_lexicon)
		return (NULL);
	return (begin_lexicon);
}
