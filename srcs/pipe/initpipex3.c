/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initpipex3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:02:45 by rmonacho          #+#    #+#             */
/*   Updated: 2022/05/26 15:58:09 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"
#include "../../incs/parsing.h"

void	ft_freetabenvp(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**seterrno_null(int i)
{
	errno = i;
	return (NULL);
}

char	**ft_convert2(char **envp)
{
	int		i;
	char	**temp;

	i = 0;
	while (envp[i] != NULL)
		i++;
	temp = malloc(sizeof(char *) * (i + 1));
	if (temp == NULL)
		return (seterrno_null(1));
	temp[i] = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		temp[i] = ft_strdup(envp[i]);
		if (temp[i] == NULL)
		{
			ft_freetabenvp(temp);
			return (seterrno_null(1));
		}
		i++;
	}
	return (temp);
}

t_list	*ft_convlist(char **envp)
{
	int		i;
	t_list	*envpl;
	t_list	*temp;
	char	*token;

	i = 0;
	envpl = NULL;
	if (envp == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		token = ft_strdup(envp[i]);
		temp = ft_lstnew(token);
		if (token == NULL || temp == NULL)
		{
			errno = 1;
			ft_lstclear(&envpl, &free);
			return (NULL);
		}
		ft_lstadd_back(&envpl, temp);
		i++;
	}
	return (envpl);
}
