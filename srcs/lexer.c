/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:35:09 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/24 16:46:18 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static int	get_cmdnb(t_list *lst)
{
	int	cmd_nb;

	cmd_nb = 0;
	if (lst)
		cmd_nb = 1;
	while (lst)
	{
		if (!ft_strncmp(get_token(lst), "|\0", 2))
			cmd_nb++;
		lst = lst->next;
	}
	return (cmd_nb);
}

static t_list	**init_heredocs(int cmd_nb)
{
	int		i;
	t_list	**heredocs;

	i = -1;
	heredocs = malloc(sizeof(t_list *) * (cmd_nb + 1));
	if (!heredocs)
		return (NULL);
	while (++i < cmd_nb)
	{
		heredocs[i] = ft_lstnew(NULL);
		if (!heredocs[i])
			return (free_heredocs(heredocs));
	}
	heredocs[i] = NULL;
	return (heredocs);
}

static int	init_chevrons_and_cmd(t_mini *mini)
{
	int	i;

	i = -1;
	mini->heredocs = init_heredocs(mini->nbc);
	mini->infile = malloc(sizeof(t_inout) * (mini->nbc + 1));
	mini->outfile = malloc(sizeof(t_inout) * (mini->nbc + 1));
	mini->commands = malloc(sizeof(char **) * (mini->nbc + 1));
	if (!mini->heredocs || !mini->infile || !mini->outfile || !mini->commands)
		return (0);
	while (++i < mini->nbc)
	{
		mini->infile[i].type = 0;
		mini->infile[i].files = NULL;
	}
	i = -1;
	while (++i < mini->nbc)
	{
		mini->outfile[i].type = 0;
		mini->outfile[i].files = NULL;
	}
	return (1);
}

t_list	*lexer(char *buffer, t_mini *mini)
{
	t_list	*begin_lexicon;

	begin_lexicon = tokenize(buffer);
	if (!begin_lexicon)
		return (NULL);
	mini->nbc = get_cmdnb(begin_lexicon);
	if (!init_chevrons_and_cmd(mini))
	{
		free_mini(mini);
		ft_lstclear(&begin_lexicon, &lst_del);
		return (NULL);
	}
	process_chevrons(&begin_lexicon, mini);
	if (!begin_lexicon)
		return (NULL);
	return (begin_lexicon);
}
