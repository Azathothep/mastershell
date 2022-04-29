/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:35:12 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/04/29 15:24:20 by fbelthoi         ###   ########.fr       */
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
char	*translate(char const *token, int (*chunk)(char const *),
			char *(*f)(char *, t_mini *), t_mini *mini);
t_list	*cut_list(char const *s, int (*f)(char const *));
int		chunk_wquotes(char const *s);
int		chunk_nquotes(char const *s);
char	*tl_only_env(char *s, t_mini *mini);
char	*tl_all(char *token, t_mini *mini);
int		process_chevrons(t_list **begin_lexicon, t_mini *mini);
int		format_ok(char const *filename);
char	*get_heredoc(t_list *lst, t_mini *mini);
int		parse_error(const char *s);

//signals
void	ft_sigint_interactive(int signal);
void	ft_sigquit_interactive(int signal);
int		ft_signal_default( void );
int		ft_init_signals_interactive( void );
int		ft_init_signals_heredoc( void );
int		ft_signal_silence( void );

//lst
void	remove_lst(t_list **begin_lst, t_list *to_del);
t_list	*pop_lst(t_list **begin_lst, t_list *to_del);
void	insert_lst(t_list **begin_lst, t_list *lst, t_list *prev_lst);
void	replace_content(t_list *lst, char *token);
char	*lst_joinstr(t_list **begin_lst);
void	pop_pile(t_list **begin_lst);
char	*get_token(t_list *lst);
void	lst_del(void *content);

//free
t_list	**free_heredocs(t_list **heredocs);
void	free_mini(t_mini *mini);
char	***free_cmd(char ***commands);
int		ft_free(void *p);

//to delete
void	display_parsing(t_mini *mini);
void	print_lst(t_list **begin_lst);

#endif
