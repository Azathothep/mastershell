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

#include "../incs/parsing.h"
#include "../incs/mini.h"
#include "../incs/lib.h"

static void	add_nl(t_list **begin_lst)
{
	t_list	*lst;
	char	*nline;

	lst = *begin_lst;
	if (!lst)
		return ;
	while (lst)
	{
		nline = ft_strjoin(get_token(lst), "\n");
		if (!nline)
		{
			errno = 1;
			ft_lstclear(begin_lst, &lst_del);
			return ;
		}
		ft_free(lst->content);
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
	return (str);
}

static void	process_input(char *input, t_list **begin_lst, int exit_status)
{
	t_list	*lst;
	char	*translation;

	lst = NULL;
	translation = translate(input, &chunk_nquotes, &tl_only_env,
			exit_status);
	if (!translation)
	{
		errno = 1;
		return ;
	}
	lst = ft_lstnew(translation);
	if (!lst)
	{
		errno = 1;
		ft_free(translation);
		ft_lstclear(begin_lst, &lst_del);
		return ;
	}
	ft_lstadd_back(begin_lst, lst);
}

char	*add_input(char *del, int exit_status)
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
			ft_free (input);
			break ;
		}
		process_input(input, &begin_lst, exit_status);
		ft_free (input);
		if (!begin_lst)
			return (NULL);
	}
	str = make_str(begin_lst);
	ft_lstclear(&begin_lst, &lst_del);
	return (str);
}
