/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:35:12 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/03/15 11:29:24 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <stddef.h>
# include "../libft/libft.h"

char	**lexer(char *prompt);
char	***parser(char **lexicon);
char	***free_cmd(char ***commands);
void	free_lexicon(char **lexicon);
char	**ft_free_split(char **tab);
char	**tokenize(char const *s);
char	**cut(char const *token, char const *mode);
char	**interpreter(char **lexicon);
int		chunk_wquotes(char const *s);
int		chunk_nquotes(char const *s);
int		tabsize(char **tab);
char	*append(char *str, char *add);

#endif