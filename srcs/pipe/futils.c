/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   futils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:09:12 by rmonacho          #+#    #+#             */
/*   Updated: 2022/03/30 15:20:26 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipe.h"

int	ft_openin(t_inout *lfiles, int j)
{
	int		i;
	int		fd;
	char	test[1];
	t_list	*temp;

	i = 0;
	temp = lfiles[j].files;
	if (temp == NULL)
		return (0);
	while (temp->next != NULL)
	{
		fd = open(temp->content, O_RDONLY);
		if (fd < 0)
			return (ft_seterrin(i));
		if (read(fd, test, 1) == -1)
			return (ft_seterrin(i));
		if (close(fd) == -1)
		{
			errno = 11;
			return (-1);
		}
		i++;
		temp = temp->next;
	}
	return (0);
}

int	ft_openout(t_inout *lfiles, int j)
{
	int		i;
	int		fd;
	t_list	*temp;

	i = 0;
	temp = lfiles[j].files;
	if (temp == NULL)
		return (0);
	while (temp->next != NULL)
	{
		if (lfiles[j].type == 0)
			fd = open(temp->content, R | C | T, I | W | G | H);
		else
			fd = open(temp->content, R | C | T | P, I | W | G | H);
		if (fd < 0)
		{
			ft_seterrout();
			return (i);
		}
		if (close(fd) == -1)
			return (ft_seterrno(11));
		i++;
		temp = temp->next;
	}
	return (0);
}

char	**ft_convert(t_list *envpl)
{
	int		i;
	char	**envp;

	i = ft_lstsize(envpl);
	envp = malloc(sizeof(char *) * (i + 1));
	if (envp == NULL)
		return (NULL);
	envp[i] = NULL;
	i = 0;
	while (envpl != NULL)
	{
		envp[i] = ft_strdup(envpl->content);
		if (envp[i] == NULL)
			return (NULL);
		i++;
		envpl = envpl->next;
	}
	return (envp);
}
