/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:35:09 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/17 12:08:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

t_list	*lexer(char *buffer, int exit_status)
{
	char	**lexicon;
	t_list	*begin_lexicon;

	lexicon = tokenize(buffer);
	if (!lexicon)
		return (NULL);
	begin_lexicon = interpreter(lexicon, exit_status);
	free_tabtwo(lexicon);
	if (!begin_lexicon)
		return (NULL);
	return (begin_lexicon);
}
