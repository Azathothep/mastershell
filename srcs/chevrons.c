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

// static char	*pull_all_quotes(char *s)
// {
// 	int		i;
// 	int		len;
// 	char	*ret;
// 	char	**cut_tab;
	
// 	i = -1;
// 	ret = NULL;
// 	cut_tab = cut(s, "w_quotes");
// 	if (!cut_tab)
// 		return (NULL);
// 	while (cut_tab[++i])
// 	{
// 		len = ft_strlen(cut_tab[i]);
// 		if ((cut_tab[i][0] == '\'' && cut_tab[i][len - 1] == '\'')
// 			|| (cut_tab[i][0] == '\"' && cut_tab[i][len - 1] == '\"'))
// 			ret = append(ret, pull_quotes(cut_tab[i]));
// 		else
// 			ret = append(ret, ft_strdup(cut_tab[i]));
// 		if (!ret)
// 			return (NULL);
// 	}
// 	return (ret);
// }

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
		input = double_quotes(input, 0); //exit_status
		str = append(str, input);
		if (!str)
			return (NULL); //free all
	}
	return (str);
}