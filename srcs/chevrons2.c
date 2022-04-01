/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevrons2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:40:00 by marvin            #+#    #+#             */
/*   Updated: 2022/04/01 14:40:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include "../incs/mini.h"
#include "../incs/lib.h"

int	format_ok(char const *filename)
{
	if (!filename || (!ft_isalpha(filename[0]) && filename[0] != '$'))
		return (0);
	return (1);
}

char	*get_heredoc(t_list *lst, int exit_status)
{
	char	*token;
	char	*del;

	token = get_token(lst);
	del = get_token(lst->next);
	if (!del || !format_ok(del))
	{
		if (!del || del[0] == '\0')
			del = "\\n";
		errno = 100;
		printf("mastershell: syntax error near '%s' <-(TO VERIFY)\n", del);
		return (NULL);
	}
	else
		token = add_input(del, exit_status);
	return (token);
}
