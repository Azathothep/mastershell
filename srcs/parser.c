/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:35:06 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/15 11:27:44 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include <stdlib.h>

char	***free_cmd(char ***commands)
{
	int	i;
	int	j;

	i = -1;
	if (commands)
	{
		while (commands[++i])
		{
			j = -1;
			while (commands[i][++j])
				free(commands[i][j]);
			free(commands[i]);
		}
		free(commands);
		commands = NULL;
	}
	return (NULL);
}

static int	get_cmd_size(char **lexicon)
{
	int	i;

	i = 0;
	while (lexicon[i] && ft_strncmp(lexicon[i], "|", 1))
		i++;
	return (i);
}

static char	**get_cmd_line(char **lexicon)
{
	char	**cmd_line;
	int		cmd_size;
	int		i;

	i = -1;
	cmd_size = get_cmd_size(lexicon);
	cmd_line = malloc(sizeof(char *) * (cmd_size + 1));
	if (!cmd_line)
		return (NULL);
	while (++i < cmd_size)
	{
		cmd_line[i] = ft_strdup(lexicon[i]);
		if (!cmd_line[i])
			return (NULL);
	}
	cmd_line[i] = NULL;
	return (cmd_line);
}

static int	get_cmd_nb(char **lexicon)
{
	int	cmd_nb;
	int	i;

	cmd_nb = 1;
	i = -1;
	while (lexicon[++i])
		if (!ft_strncmp(lexicon[i], "|", 1))
			cmd_nb++;
	return (cmd_nb);
}

char	***parser(char **lexicon)
{
	char	***commands;
	int		cmd_nb;
	int		i;

	i = -1;
	cmd_nb = get_cmd_nb(lexicon);
	commands = malloc(sizeof(char **) * (cmd_nb + 1));
	if (!commands)
		return (NULL);
	while (++i < cmd_nb)
	{
		commands[i] = get_cmd_line(lexicon);
		if (!commands[i])
			return (free_cmd(commands));
		lexicon += get_cmd_size(lexicon) + 1;
	}
	commands[i] = NULL;
	return (commands);
}
