/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:35:06 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/28 11:12:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include "../incs/mini.h"
#include "../incs/lib.h"

static int	process_lexiconline(t_list **begin_lexicon, int exit_status)
{
	t_list	*lst;
	char	*token;
	int		size;

	size = 0;
	lst = *begin_lexicon;
	while (lst && ft_strncmp(get_token(lst), "|\0", 2))
	{
		size++;
		token = translate(get_token(lst), &chunk_wquotes, &tl_all, exit_status);
		if (!token)
		{
			ft_lstclear(begin_lexicon, &lst_del);
			return (-1);
		}
		if (token != lst->content)
			replace_content(lst, token);
		if (token[0] == '\0')
			remove_lst(begin_lexicon, lst);
		lst = lst->next;
	}
	return (size);
}

static char	**get_cmdline(t_list **begin_lexicon, int exit_status)
{
	char	**cmd_line;
	int		cmd_size;
	int		i;

	i = -1;
	cmd_size = process_lexiconline(begin_lexicon, exit_status);
	if (cmd_size == 0)
		cmd_size += 0;
	cmd_line = malloc(sizeof(char *) * (cmd_size + 1));
	if (!cmd_line)
		return (NULL);
	while (++i < cmd_size)
	{
		cmd_line[i] = ft_strdup(get_token(*begin_lexicon));
		if (!cmd_line[i])
			return (NULL);
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
	while (++i < mini->nbc)
	{
		mini->commands[i] = get_cmdline(begin_lexicon, mini->exit_status);
		if (!mini->commands[i])
			return (0);
	}
	mini->commands[i] = NULL;
	return (1);
}
