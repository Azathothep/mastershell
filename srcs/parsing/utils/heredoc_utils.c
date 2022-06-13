/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:28:40 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/06/13 11:32:02 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/parsing.h"
#include "../../../incs/lib.h"

char	*set_errno_null(int n)
{
	errno = n;
	return (NULL);
}

char	*ft_addalloc(char *s, int size)
{
	char	*new_line;
	int		len;

	len = ft_strlen(s);
	new_line = malloc(sizeof(char) * (len + size + 1));
	if (!new_line)
	{
		errno = 1;
		return (NULL);
	}
	ft_bzero(new_line, len + size + 1);
	ft_strlcpy(new_line, s, len + 1);
	free(s);
	return (new_line);
}

char	*make_line(int fd)
{
	char	*content;
	int		i;

	i = 0;
	content = malloc(sizeof(char) * 41);
	if (!content)
	{
		errno = 1;
		return (NULL);
	}
	ft_bzero(content, 41);
	while (content && read(fd, content + (i * 40), 40))
	{
		content = ft_addalloc(content, 40);
		if (!content)
			return (NULL);
		i++;
	}
	close(fd);
	return (content);
}
