/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:06:04 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/04/22 15:28:14 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/lib.h"
#include "../incs/parsing.h"
#include <termios.h>

void ft_sigint(int signal)
{	
	signal += 0;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void ft_sigquit(int signal)
{	
	signal += 0;
}