/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:35:12 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/24 17:07:44 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <stddef.h>
# include "../incs/lib.h"
# include "../incs/mini.h"

t_list	*tokenize(char const *s);
t_list	*lexer(char *buffer, t_mini *mini);
int		parser(t_list **begin_lexicon, t_mini *mini);
int		isenv(char c);
char	*pull_quotes(char *s);
char 	*translate(char const *token, char *(*f)(char *, int), int exit_status);
t_list	*cut_list(char const *s, int (*f)(char const *));
int		chunk_wquotes(char const *s);
int		chunk_nquotes(char const *s);
char	*add_input(char *del, char *mode);
char	*tl_only_env(char *s, int exit_status);
char	*tl_all(char *token, int exit_status);
void	process_chevrons(t_list **begin_lexicon, t_mini *mini);

//lst
t_list	*remove_lst(t_list **begin_lst, t_list *lst, t_list *prev_lst);
void	insert_lst(t_list **begin_lst, t_list *lst, t_list *prev_lst);
void	replace_content(t_list *lst, char *token);
char	*lst_joinstr(t_list **begin_lst);
void	pop_lst(t_list **begin_lst);
char	*get_token(t_list *lst);
void	lst_del(void *content);

//free
t_list	**free_heredocs(t_list **heredocs);
void	free_mini(t_mini *mini);
char	***free_cmd(char ***commands);
char	**free_tabtwo(char **tab);

#endif