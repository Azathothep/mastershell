/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:35:12 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/17 12:12:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <stddef.h>
# include "../incs/lib.h"
# include "../incs/mini.h"

t_list	*lexer(char *buffer, int exit_status);
t_mini	parser(t_list **begin_lexicon, t_mini mini);
int		get_cmdnb(t_list *lst);
char	**get_cmdline(t_list *lst);
char	***free_cmd(char ***commands);
char	**free_tabtwo(char **tab);
char	**tokenize(char const *s);
char	**cut(char const *token, char const *mode);
t_list	*interpreter(char **lexicon, int exit_status);
int		isenv(char c);
char	*replace_env(char const *s, int exit_status);
char	*pull_quotes(char const *s);
char	*double_quotes(char const *s, int exit_status);
void	lst_del(void *content);
int		chunk_wquotes(char const *s);
int		chunk_nquotes(char const *s);
int		tabsize(char **tab);
char	*append(char *str, char *add);

#endif