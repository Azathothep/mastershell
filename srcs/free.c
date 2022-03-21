#include "../incs/parsing.h"
#include <stdlib.h>
#include <stdio.h>

char	**free_tabtwo(char **tab)
{
	int	index;

	index = -1;
	if (!tab)
		return (NULL);
	while (tab[++index])
		free(tab[index]);
	free(tab);
	tab = NULL;
	return (NULL);
}

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

void	lst_del(void *content)
{
	free((char *)content);
}
