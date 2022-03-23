/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:31:39 by marvin            #+#    #+#             */
/*   Updated: 2022/03/16 11:31:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include "../incs/lib.h"

char	*replace_env(char const *s, int exit_status)
{
	char	*env;

	if (s[1] == '?')
		env = ft_itoa(exit_status);
	else
	{
		env = getenv(&s[1]);
		if (!env)
			env = ft_strdup("");
	}
	if (!env)
		return (NULL);
	return (env);
}

char	*pull_quotes(char *s)
{
	int		len;

	len = ft_strlen(s);
	ft_memmove(s, s + 1, len);
	if (len > 1)
		s[len - 2] = '\0';
	return (s);
}
