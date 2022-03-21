/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:41:22 by marvin            #+#    #+#             */
/*   Updated: 2022/03/17 12:41:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "../incs/parsing.h"
#include "../incs/mini.h"
#include "../incs/lib.h"

static void	add_nl(t_list **begin_lst)
{
	t_list	*lst;
	char	*nline;

	lst = *begin_lst;
	while (lst->next)
	{
		nline = ft_strjoin(get_token(lst), "\n");
		if (!nline)
		{
			ft_lstclear(begin_lst, &lst_del);
			return ;
		}
		free(lst->content);
		lst->content = nline;
		lst = lst->next;
	}
}

static char	*make_str(t_list *begin_lst)
{
	char	*str;

	add_nl(&begin_lst);
	if (!begin_lst)
		return (NULL);
	str = lst_joinstr(&begin_lst);
	ft_lstclear(&begin_lst, &lst_del);
	return (str);
}

static void	process_input(char *input, t_list **begin_lst, char *mode)
{
	t_list	*lst;
	char	*translation;

	if (!ft_strncmp(mode, "n_quoted", 8))
		translation = translate(input, &tl_only_env, 0); //exit_status
	else
		translation = ft_strdup(input);
	lst = ft_lstnew(translation);
	if (!translation || !lst)
	{
		ft_lstclear(begin_lst, &lst_del);
		return ;
	}
	ft_lstadd_back(begin_lst, lst);
}

char	*add_input(char *del, char *mode)
{
	t_list	*begin_lst;
	char	*str;
	char	*input;
	int		len_del;

	begin_lst = NULL;
	len_del = ft_strlen(del);
	while (1)
	{
		input = readline("> ");
		if (!ft_strncmp(input, del, len_del + 1))
		{
			free (input);
			break ;
		}
		process_input(input, &begin_lst, mode);
		free (input);
		if (!begin_lst)
			return (NULL);
	}
	str = make_str(begin_lst);
	return (str);
}
