/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:34:57 by fbelthoi          #+#    #+#             */
/*   Updated: 2022/06/08 11:44:11 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../incs/parsing.h"
#include "../incs/mini.h"
#include "../incs/lib.h"
#include "../incs/pipe.h"
#include <termios.h>

static int	errno_ok(void)
{
	if (errno == 1)
	{
		return (0);
	}
	return (1);
}

static int	isempty(char *line)
{
	return (!ft_strncmp(line, "", 1));
}

static t_mini	init_mini(char **envp)
{
	t_mini	mini;

	mini.commands = NULL;
	mini.infile = NULL;
	mini.outfile = NULL;
	mini.errfile = NULL;
	mini.nbc = 0;
	mini.pipex = NULL;
	mini.exit_status = 0;
	mini.infile = NULL;
	mini.outfile = NULL;
	mini.heredocs = NULL;
	mini.pid = NULL;
	mini.pipex = NULL;
	mini.envpl = NULL;
	mini.infhere = NULL;
	mini.envp = ft_convert2(envp);
	if (!mini.envp)
		return (mini);
	mini.envpl = ft_convlist(envp);
	return (mini);
}

static void	launch_shell(t_mini *mini)
{
	t_list	*begin_lexicon;
	char	*buffer;

	while (errno_ok())
	{
		errno = 0;
		ft_init_signals_interactive();
		ft_termios_noctl(mini);
		buffer = readline("-> mishell #> ");
		if (!isempty(buffer))
		{
			add_history(buffer);
			begin_lexicon = lexer(buffer, mini);
			ft_free (buffer);
			if (!begin_lexicon)
				ft_lstclear(&begin_lexicon, &lst_del);
			else if (parser(&begin_lexicon, mini))
				ft_start_pipe(mini);
			free_mini(mini);
		}
		if (!buffer)
			ft_exit(mini, NULL, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	argv += 0;
	if (argc > 1)
	{
		printf("no arguments required\n");
		return (0);
	}
	errno = 0;
	g_exitstatus = 0;
	mini = init_mini(envp);
	if (!(mini.envp) || !(mini.envpl))
	{
		ft_freeenvp((mini.envp), (mini.envpl));
		free_mini(&mini);
		exit(1);
	}
	ft_set_termios_save(&mini);
	ft_termios_noctl(&mini);
	ft_eraseold(&mini);
	launch_shell(&mini);
	ft_termios_ctl(&mini);
	ft_freeenvp((mini.envp), (mini.envpl));
	return (0);
}
