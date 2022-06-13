/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:35:06 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/06/13 11:01:08 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parsing.h"
#include "../../incs/mini.h"
#include "../../incs/lib.h"

static char	**get_cmdline(t_list *lexer_line)
{
	char	**cmd_line;
	t_list	*lst;
	int		cmd_size;
	int		i;

	i = -1;
	cmd_size = ft_lstsize(lexer_line);
	if (cmd_size == 0)
		return (NULL);
	cmd_line = malloc(sizeof(char *) * (cmd_size + 1));
	if (!cmd_line)
		return (set_errno(1));
	lst = lexer_line;
	while (++i < cmd_size)
	{
		cmd_line[i] = ft_strdup(get_token(lst));
		if (!cmd_line[i])
			return (free_cmdline(cmd_line));
		lst = lst->next;
	}
	cmd_line[i] = NULL;
	return (cmd_line);
}

t_list	*next_cmdstart_lst(t_list *begin_lst)
{
	t_list	*lst;
	t_list	*next;
	t_list	*prev;

	lst = begin_lst;
	prev = NULL;
	while (lst && ft_strncmp(get_token(lst), "|\0", 2) != 0)
	{
		prev = lst;
		lst = lst->next;
	}
	if (lst)
	{
		next = lst->next;
		ft_lstdelone(lst, &lst_del);
		lst = NULL;
		if (prev)
			prev->next = NULL;
		return (next);
	}
	else
		return (NULL);
}

t_list	**create_lexertab(t_list **begin_lexicon, int nbc)
{
	int		i;
	t_list	*lst;
	t_list	**begin_lexertab;

	i = -1;
	begin_lexertab = malloc(sizeof(t_list *) * (nbc + 1));
	if (!begin_lexertab)
		return (NULL);
	lst = *begin_lexicon;
	while (++i < nbc)
	{
		begin_lexertab[i] = lst;
		lst = next_cmdstart_lst(lst);
	}
	begin_lexertab[i] = NULL;
	return (begin_lexertab);
}

int	parser(t_list **begin_lexicon, t_mini *mini)
{
	int		i;
	t_list	**begin_lexertab;

	i = -1;
	begin_lexertab = create_lexertab(begin_lexicon, mini->nbc);
	if (!begin_lexertab)
		return (0);
	translation_lexertab(begin_lexertab, mini);
	while (++i < mini->nbc)
	{
		mini->commands[i] = get_cmdline(begin_lexertab[i]);
		if (!mini->commands[i] && errno == 1)
			return (free_lexertab(begin_lexertab));
	}
	free_lexertab(begin_lexertab);
	mini->commands[i] = NULL;
	return (1);
}
