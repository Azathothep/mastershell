/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:41:22 by marvin            #+#    #+#             */
/*   Updated: 2022/03/17 12:41:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/parsing.h"
#include "../incs/mini.h"
#include "../incs/lib.h"
#include "../incs/pipe.h"

static char	*seterrno_null(int n)
{
	errno = n;
	return (NULL);
}

static char	*ft_addalloc(char *s, int size)
{
	char	*new_line;
	int		len;

	len = ft_strlen(s);
	new_line = malloc(sizeof(char) * (len + size + 1));
	if (!new_line)
	{
		errno = 1;
		return (NULL);
	}
	ft_bzero(new_line, len + size + 1);
	ft_strlcpy(new_line, s, len + 1);
	free(s);
	return (new_line);
}

static char	*make_line(int fd)
{
	char	*content;
	int		i;

	i = 0;
	content = malloc(sizeof(char) * 41);
	if (!content)
	{
		errno = 1;
		return (NULL);
	}
	ft_bzero(content, 41);
	while (content && read(fd, content + (i * 40), 40))
	{
		content = ft_addalloc(content, 40);
		if (!content)
			return (NULL);
		i++;
	}
	close(fd);
	return (content);
}

static int	fill_heredoc(int pipe_fd[2], char *del, t_mini *mini)
{
	char	*input;
	char	*translation;
	int		len_del;

	close(pipe_fd[0]);
	ft_init_signals_heredoc();
	len_del = ft_strlen(del);
	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		if (!ft_strncmp(input, del, len_del + 1))
		{
			ft_free (input);
			break ;
		}
		translation = translate_heredoc(input, mini);		
		ft_free (input);
		if (!translation)
			exit(1);
		write(pipe_fd[1], translation, ft_strlen(translation));
		write(pipe_fd[1], "\n", 1);
	}
	exit(0);
}

static char	*heredoc_fork(char *del, t_mini *mini)
{
	pid_t	pid;
	int		status;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (seterrno_null(1));
	pid = fork();
	if (pid == -1)
		return (seterrno_null(1));
	else if (pid == 0)
		fill_heredoc(pipe_fd, del, mini);
	else
	{
		close(pipe_fd[1]);
		ft_signal_silence();
		waitpid(pid, &status, 0);
		ft_init_signals_interactive();
		if (WIFSIGNALED(status))
			write(1, "\n", 1);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 0)
				return (make_line(pipe_fd[0]));
			else
				errno = 1;
		}
	}
	return (NULL);
}

char	*get_heredoc(t_list *lst, t_mini *mini)
{
	char	*token;
	char	*del;

	token = get_token(lst);
	del = get_token(lst->next);
	if (!del || !format_ok(del))
	{
		if (!del || del[0] == '\0')
			del = "\\n";
		parse_error("<<");
		return (NULL);
	}
	else
		token = heredoc_fork(del, mini);
	return (token);
}
