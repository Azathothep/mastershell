/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevrons.c                                         :+:      :+:    :+:   */
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

char	*add_input(char *del)
{
	char	*str;
	char	*input;
	int		len_del;

	str = NULL;
	len_del = ft_strlen(del);
	while (1)
	{
		input = readline("> ");
		if (!input)
			return (NULL); // free str
		if (!ft_strncmp(input, del, len_del))
		{
			free (input);
			break ;
		}
		str = append(str, input);
		if (!str)
			return (NULL); //free all
	}
	return (str);
}