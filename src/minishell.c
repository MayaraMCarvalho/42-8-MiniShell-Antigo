/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:02:28 by macarval          #+#    #+#             */
/*   Updated: 2023/04/07 14:55:31 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/redirections.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*text;

	if (argc && argv)
	{}
	shell.envp = envp;
	while (1)
	{

		text = make_text();
		shell.line = readline(text);
		free(text);
		if (shell.line)
		{
			add_history (shell.line);
			//shell = make_shell(shell.line);

			// Configuração de teste dos buildins
			char	**split;

			split = ft_split(shell.line, ' ');
			if (split[0] == '<')
				redirections(split, envp);
			shell.command = split[0];
			shell.flag = ft_strdup("-n");
			shell.content = split[1];

			//
			if (is_command(shell))
				printf("bash: %s: command not found\n", shell.command);
			free(shell.line);
		}
	}
	return (0);
}

char	*make_text(void)
{
	char	*text;
	char	buf[256];
	char	*path;

	path = getcwd(buf, 256);
	path = ft_substr(path, ft_strlen(getenv("HOME")), ft_strlen(path));
	text = ft_strjoin(path, "$ ");
	free(path);
	return (text);
}
