/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:06:32 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/05/17 16:46:45 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/mini.h"
#include <termios.h>

void	ft_termios_ctl(t_mini *mini)
{
	tcsetattr(0, 0, &(mini->termios_save));
}

void	ft_termios_noctl(t_mini *mini)
{
	struct termios	termios_new;

	termios_new = mini->termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_new);
}

void	ft_set_termios_save(t_mini *mini)
{
	tcgetattr(0, &(mini->termios_save));
}
