/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:01:30 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/06/13 11:20:33 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/parsing.h"
#include "../../../incs/lib.h"

char	**set_errno(int i)
{
	errno = i;
	return (NULL);
}

char	**free_cmdline(char **cmd_line)
{
	int	i;

	i = -1;
	while (cmd_line[++i])
		free(cmd_line[i]);
	free(cmd_line);
	return (NULL);
}

int	free_lexertab(t_list **begin_lexertab)
{
	int	i;

	i = -1;
	while (begin_lexertab[++i])
	{
		ft_lstclear(&begin_lexertab[i], &lst_del);
	}
	free (begin_lexertab);
	return (0);
}
