/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:35:09 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/15 11:32:30 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void	free_lexicon(char **lexicon)
{
	int	i;

	i = -1;
	if (!lexicon)
		return ;
	while (lexicon[++i])
		free(lexicon[i]);
	free(lexicon);
	lexicon = NULL;
}

char	**lexer(char *buffer)
{
	char	**lexicon;
	char	**translation;

	lexicon = tokenize(buffer);
	if (!lexicon)
		return (NULL);
	translation = interpreter(lexicon);
	ft_free_split(lexicon);
	if (!translation)
		return (NULL);
	return (translation);
}
