/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:35:12 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/22 10:56:49 by marvin           ###   ########.fr       */
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
t_list	*tokenize(char const *s);
void	interpreter(t_list **begin_lst, int exit_status);
int		isenv(char c);
char	*replace_env(char const *s, int exit_status);
char	*pull_quotes(char *s);
char 	*translate(char const *token, char *(*f)(char *, int), int exit_status);
void	lst_del(void *content);
int		chunk_wquotes(char const *s);
int		chunk_nquotes(char const *s);
char	*add_input(char *del, char *mode);
char	*get_token(t_list *lst);
char	*lst_joinstr(t_list **begin_lst);
t_list	*cut_list(char const *s, int (*f)(char const *));
char	*tl_only_env(char *s, int exit_status);
void	remove_lst(t_list **begin_lst, t_list *lst, t_list *prev_lst);
void	insert_lst(t_list **begin_lst, t_list *lst, t_list *prev_lst);
void	process_chevrons(t_list **begin_lexicon, t_list *lst, t_list *prev_lst, t_mini *mini);

#endif