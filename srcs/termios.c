/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelthoi <fbelthoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:06:32 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/05/09 13:24:28 by fbelthoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>

void	ft_termios_ctl()
{
	struct termios	termios_new;

	tcgetattr(0, &termios_new);
	termios_new.c_lflag &= ECHOCTL;
	tcsetattr(0, 0, &termios_new);
}

void	ft_termios_noctl()
{
	struct termios	termios_new;

	tcgetattr(0, &termios_new);
	termios_new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_new);
}