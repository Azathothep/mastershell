/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:35:06 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/21 11:34:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include "../incs/mini.h"
#include "../incs/lib.h"

static void	remove_lst(t_list **begin_lst, t_list *lst, t_list *prev_lst)
{
	if (prev_lst)
		prev_lst->next = lst->next;
	else
		*begin_lst = lst->next;
	ft_lstdelone(lst, &lst_del);
}

static void	insert_lst(t_list *lst, t_list *lst_new)
{
	t_list	*next_lst;

	next_lst = lst->next;
	lst->next = lst_new;
	lst_new->next = next_lst;
}

static t_mini	process_datas(t_list **begin_lexicon, t_mini mini)
{
	t_list	*lst;
	t_list	*lst_new;
	t_list	*prev_lst;
	char	*token;

	lst = *begin_lexicon;
	prev_lst = NULL;
	while (lst)
	{
		token = get_token(lst);
		if (token[0] == '\0')
			remove_lst(begin_lexicon, lst, prev_lst);
		else if (!ft_strncmp("<<\0", token, 3))
		{
			token = add_input(get_token(lst->next));
			lst_new = ft_lstnew(token);
			if (!token || !lst_new)
				return (mini); // free_all
			remove_lst(begin_lexicon, lst->next, lst);
			remove_lst(begin_lexicon, lst, prev_lst);
			insert_lst(prev_lst, lst_new);
		}
		prev_lst = lst;
		lst = lst->next;
	}
	mini.nbc = 0;
	return (mini);
}

static char	***get_commands(t_list *lst)
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
	return (commands);
}

t_mini	parser(t_list **begin_lexicon, t_mini mini)
{
	mini = process_datas(begin_lexicon, mini);
	mini.commands = get_commands(*begin_lexicon);
	return (mini);
}
