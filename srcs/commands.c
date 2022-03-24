/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:36:51 by marvin            #+#    #+#             */
/*   Updated: 2022/03/16 11:36:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include "../incs/mini.h"
#include "../incs/lib.h"

static int	get_linesize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst && ft_strncmp(get_token(lst), "|\0", 2))
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	get_cmdnb(t_list *lst)
{
	int	cmd_nb;

	cmd_nb = 0;
	if (lst)
		cmd_nb = 1;
	while (lst)
	{
		if (!ft_strncmp(get_token(lst), "|\0", 2))
			cmd_nb++;
		lst = lst->next;
	}
	return (cmd_nb);
}

char	**get_cmdline(t_list *lst)
{
	char	**cmd_line;
	int		cmd_size;
	int		i;

	i = -1;
	cmd_size = get_linesize(lst);
	if (cmd_size == 0)
		printf("lol\n");
	cmd_line = malloc(sizeof(char *) * (cmd_size + 1));
	if (!cmd_line)
		return (NULL);
	while (++i < cmd_size)
	{
		cmd_line[i] = ft_strdup(get_token(lst));
		if (!cmd_line[i])
			return (NULL);
		lst = lst->next;
	}
	cmd_line[i] = NULL;
	return (cmd_line);
}
