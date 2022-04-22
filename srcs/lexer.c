/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:35:09 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/04/22 12:14:49 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include "../incs/lib.h"

static int	get_cmdnb(t_list *lst)
{
	int	cmd_nb;

	cmd_nb = 0;
	if (lst)
		cmd_nb = 1;
	while (lst)
	{
		if (!ft_strncmp(get_token(lst), "|\0", 2))
		{
			cmd_nb++;
			if (!ft_strncmp(get_token(lst->next), "|\0", 2))
			{
				parse_error("|");
				return (-1);
			}
		}
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
	{
		errno = 1;
		return (NULL);
	}
	while (++i < cmd_nb)
	{
		heredocs[i] = ft_lstnew(NULL);
		if (!heredocs[i])
		{
			errno = 1;
			return (free_heredocs(heredocs));
		}
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
	mini->errfile = malloc(sizeof(t_inout) * (mini->nbc + 1));
	mini->commands = malloc(sizeof(char **) * (mini->nbc + 1));
	mini->infhere = malloc(sizeof(int) * (mini->nbc));
	if (!mini->heredocs || !mini->infile || !mini->outfile
		|| !mini->errfile || !mini->commands || !mini->infhere)
	{
		errno = 1;
		return (0);
	}
	while (++i < mini->nbc)
	{
		mini->infile[i].type = 0;
		mini->infile[i].files = NULL;
		mini->outfile[i].type = 0;
		mini->outfile[i].files = NULL;
		mini->errfile[i].type = 0;
		mini->errfile[i].files = NULL;
		mini->commands[i] = NULL;
		mini->infhere[i] = 0;
	}
	return (1);
}

t_list	*lexer(char *buffer, t_mini *mini)
{
	t_list	*begin_lexicon;

	begin_lexicon = tokenize(buffer);
	if (!begin_lexicon)
		return (NULL);
	if (!ft_strncmp(get_token(begin_lexicon), "|\0", 2))
	{
		parse_error("|");
		ft_lstclear(&begin_lexicon, &lst_del);
		return (NULL);
	}
	mini->nbc = get_cmdnb(begin_lexicon);
	if (mini->nbc < 0)
	{
		ft_lstclear(&begin_lexicon, &lst_del);
		return (NULL);
	}
	if (!init_chevrons_and_cmd(mini)
		|| !process_chevrons(&begin_lexicon, mini))
	{
		ft_lstclear(&begin_lexicon, &lst_del);
		return (NULL);
	}
	return (begin_lexicon);
}
