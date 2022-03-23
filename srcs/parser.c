/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:35:06 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/22 10:59:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include "../incs/mini.h"
#include "../incs/lib.h"

static t_mini	process_datas(t_list **begin_lexicon, t_mini mini)
{
	t_list	*lst;
	t_list	*prev_lst;
	char	*token;

	lst = *begin_lexicon;
	prev_lst = NULL;
	while (lst)
	{
		token = get_token(lst);
		if (token[0] == '\0')
			remove_lst(begin_lexicon, lst, prev_lst);
		else if (ft_inbase(token[0], "<>"))
			process_chevrons(begin_lexicon, lst, prev_lst, &mini);
		if (!*begin_lexicon)
		{
			mini.parse_error = 1;
			return (mini);
		}
		prev_lst = lst;
		lst = lst->next;
	}
	mini.nbc = 0;
	return (mini);
}

static char	***get_commands(t_list *lst, t_mini *mini)
{
	int		i;
	int		cmd_nb;
	char	***commands;

	i = -1;
	cmd_nb = get_cmdnb(lst);
	commands = malloc(sizeof(char **) * (cmd_nb + 1));
	if (!commands)
		return (NULL);
	while (++i < cmd_nb)
	{
		commands[i] = get_cmdline(lst);
		if (!commands[i])
			return (free_cmd(commands));
		while (lst->next && ft_strncmp(get_token(lst), "|\0", 2))
			lst = lst->next;
		lst = lst->next;
	}
	commands[i] = NULL;
	mini->nbc = cmd_nb;
	return (commands);
}

t_mini	parser(t_list **begin_lexicon, t_mini mini)
{
	mini = process_datas(begin_lexicon, mini);
	if (mini.parse_error)
		return (mini);
	mini.commands = get_commands(*begin_lexicon, &mini);
	return (mini);
}
