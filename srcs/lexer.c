/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:35:09 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/21 14:02:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

t_list	*lexer(char *buffer, int exit_status)
{
	t_list	*begin_lexicon;

	begin_lexicon = tokenize(buffer);
	if (!begin_lexicon)
		return (NULL);
	interpreter(&begin_lexicon, exit_status);
	if (!begin_lexicon)
		return (NULL);
	return (begin_lexicon);
}
