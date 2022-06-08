/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevrons.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:16:37 by marvin            #+#    #+#             */
/*   Updated: 2022/03/21 15:16:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/parsing.h"
#include "../../../incs/mini.h"
#include "../../../incs/lib.h"

static int	errno_free(char *token)
{
	errno = 1;
	ft_free(token);
	token = NULL;
	return (0);
}

static void	add_chevron2(char const *sign, t_list *lst_new,
			t_mini *mini, t_list *lst_type, int index)
{
	int	i;

	i = 0;
	if (sign[0] == '<')
	{
		mini->infhere[index] = 0;
		ft_lstadd_back(&(mini->infile[index].files), lst_new);
		ft_lstadd_back(&(mini->infile[index].types), lst_type);
	}
	else if (sign[0] == '>' || sign[0] == '1')
	{
		if (sign[0] == '1')
			i = 1;
		if (sign[i + 1] == '>')
			*((int *)(lst_type->content)) = 1;
		ft_lstadd_back(&(mini->outfile[index].files), lst_new);
		ft_lstadd_back(&(mini->outfile[index].types), lst_type);
	}
	else if (sign[0] == '2')
	{
		if (sign[2] == '>')
			*((int *)(lst_type->content)) = 1;
		ft_lstadd_back(&(mini->errfile[index].files), lst_new);
		ft_lstadd_back(&(mini->errfile[index].types), lst_type);
	}
}

static int	add_chevron(char const *sign, t_list *lst_token, t_mini *mini, int index)
{
	t_list	*lst_new;
	t_list	*lst_type;
	char	*token;
	int		*type;

	token = get_token(lst_token);
	lst_new = NULL;
	if (!format_ok(token))
		return (parse_error(sign));
	type = malloc(sizeof(int));
	lst_new = translate_word(lst_token, mini);
	lst_type = ft_lstnew(type);
	if (!lst_new || !type || !lst_type)
	{
		errno = 1;
		ft_free(type);
		ft_lstdelone(lst_new, &lst_del);
		ft_lstdelone(lst_type, &lst_del);
		return (0);
	}
	*type = 0;
	add_chevron2(sign, lst_new, mini, lst_type, index);
	return (1);
}

static int	treat_chevron(t_list *lst, t_mini *mini, int index)
{
	char	*token;
	t_list	*lst_new;

	if (!ft_strncmp(get_token(lst), "<<", 2))
	{
		mini->infhere[index] = 1;
		token = get_heredoc(lst, mini);
		if (!token)
			return (0);
		if (mini->heredocs[index]->content == NULL)
			mini->heredocs[index]->content = token;
		else
		{
			lst_new = ft_lstnew(token);
			if (!lst_new)
				return (errno_free(token));
			ft_lstadd_back(&(mini->heredocs[index]), lst_new);
		}
	}
	else
		if (!add_chevron(get_token(lst), lst->next, mini, index))
			return (0);
	return (1);
}

int	process_chevrons(t_list **begin_lexicon, t_mini *mini)
{
	t_list	*lst;
	t_list	*temp;
	int		index;

	index = 0;
	lst = *begin_lexicon;
	while (lst)
	{
		if (!ft_strncmp(get_token(lst), "|\0", 2))
			index++;
		if (ft_inbase(get_token(lst)[0], "<>")
		|| !ft_strncmp(get_token(lst), "2>", 2)
		|| !ft_strncmp(get_token(lst), "1>", 2))
		{
			if (!treat_chevron(lst, mini, index))
				return (0);
			temp = lst->next->next;
			remove_lst(begin_lexicon, lst->next);
			remove_lst(begin_lexicon, lst);
			lst = temp;
		}
		else
			lst = lst->next;
	}
	return (1);
}
