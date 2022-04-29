/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:06:04 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/04/29 16:23:50 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/lib.h"
#include "../incs/parsing.h"
#include <termios.h>

void	ft_sigint_interactive(int signal)
{	
	signal += 0;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	//write(2, "-> mastershell #> ", 18);
	rl_redisplay();
}

int	ft_init_signals_interactive( void )
{
	signal(SIGINT, &ft_sigint_interactive);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

int	ft_init_signals_heredoc( void )
{
	signal(SIGINT, SIG_DFL);
	return (1);
}

int	ft_signal_default( void )
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	return (1);
}

int	ft_signal_silence( void )
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}
