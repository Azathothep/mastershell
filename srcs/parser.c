/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:35:06 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/05/17 16:44:49 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include "../incs/mini.h"
#include "../incs/lib.h"

static char	**set_errno(int i)
{
	errno = i;
	return (NULL);
}

static int	process_lexiconline(t_list **begin_lexicon, t_mini *mini)
{
	t_list	*lst;
	char	*token;
	int		size;

	size = 0;
	lst = *begin_lexicon;
	while (lst && ft_strncmp(get_token(lst), "|\0", 2))
	{
		size++;
		token = translate(get_token(lst), &chunk_wquotes, &tl_all, mini);
		if (!token)
			return (-1);
		if (token != lst->content)
			replace_content(lst, token);
		lst = lst->next;
	}
	return (size);
}

static char	**get_cmdline(t_list **begin_lexicon, t_mini *mini)
{
	char	**cmd_line;
	int		cmd_size;
	int		i;

	i = -1;
	cmd_size = process_lexiconline(begin_lexicon, mini);
	if (cmd_size < 0)
		return (NULL);
	cmd_line = malloc(sizeof(char *) * (cmd_size + 1));
	if (!cmd_line)
	{
		errno = 1;
		return (NULL);
	}
	while (++i < cmd_size)
	{
		cmd_line[i] = ft_strdup(get_token(*begin_lexicon));
		if (!cmd_line[i])
			return (set_errno(1));
		pop_pile(begin_lexicon);
	}
	pop_pile(begin_lexicon);
	cmd_line[i] = NULL;
	return (cmd_line);
}

int	parser(t_list **begin_lexicon, t_mini *mini)
{
	int	i;

	i = -1;
	if (!replace_all_env(begin_lexicon, mini))
		return (0);
	while (++i < mini->nbc)
	{
		mini->commands[i] = get_cmdline(begin_lexicon, mini);
		if (!mini->commands[i])
		{
			ft_lstclear(begin_lexicon, &lst_del);
			return (0);
		}
	}
	mini->commands[i] = NULL;
	return (1);
}
