/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:02:28 by macarval          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/05 15:13:32 by macarval         ###   ########.fr       */
=======
/*   Updated: 2023/05/05 20:01:58 by macarval         ###   ########.fr       */
>>>>>>> 7be836de6ad06499574f64c97c5f6070e7168d6d
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*text;

	if (argc && argv)
	{
	}
	shell.envp = envp;
	while (1)
	{
		text = make_text();
		shell.line = readline(text);
		free(text);
		if (shell.line[0] != '\0')
		{
			add_history (shell.line);
			shell = make_shell(shell.line);
			if (shell.command && is_command(shell))
				printf("bash: %s: command not found\n", shell.command);
			free_struct(shell);
			inicialize(&shell);
		}
		else
			free(shell.line);
	}
	return (0);
}

char	*make_text(void)
{
	char	*text;
	char	buf[256];
	char	*path;
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(getenv("LOGNAME"), "@");
	temp2 = ft_strjoin(temp1, getenv("NAME"));
	free(temp1);
	temp1 = ft_strjoin("\033[1;33m", temp2);
	free(temp2);
	temp2 = ft_strjoin(temp1, "\033[1;0m:\033[1;35m~");
	free(temp1);
	path = getcwd(buf, 256);
	path = ft_substr(path, ft_strlen(getenv("HOME")), ft_strlen(path));
	temp1 = ft_strjoin(temp2, path);
	free(path);
	free(temp2);
	text = ft_strjoin(temp1, "\001\033[1;0m\002$\001\033[0m\002 ");
	free(temp1);
	return (text);
}

void	inicialize(t_shell *shell)
{
	shell->line = NULL;
	shell->command = NULL;
	shell->flag = NULL;
	shell->content = NULL;
}
