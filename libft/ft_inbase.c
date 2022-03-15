/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inbase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:28:56 by marvin            #+#    #+#             */
/*   Updated: 2021/12/08 15:28:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_inbase(char c, char *base)
{
	int		i;

	i = -1;
	while (base[++i])
		if (base[i] == c)
			return (1);
	return (0);
}
