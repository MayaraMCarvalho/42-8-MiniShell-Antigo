/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:02:28 by macarval          #+#    #+#             */
/*   Updated: 2023/10/08 16:22:09 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	char		*text;

	shell.env = make_list(envp);
	shell.exit_code = 0;
	text = NULL;
	while (true && argc && argv)
	{
		text = make_text();
		inicialize(&shell);
		shell.line = strtrim_mod(readline(text), " ");
		free(text);
		if (shell.line[0] != '\0')
		{
			add_history(shell.line);
			if (make_shell(&shell))
			{
				/* Lembrando que aqui entra sua parte.
				Para os builtins funcionarem, você tem que
				usar a estrutura do t_shell:

				shell.command = BUILTIN
				shell.flag = FLAG
				shell.content = CONTENT

				Você recebe o shell->lex onde encontra as
				informações necessárias.
				lex[i][0] -> é o conteúdo de fato.
				lex[i][1] -> é a identificação do conteúdo.

				Assim, quando chamar a função abaixo e
				verify_builtins vai funcionar corretamente*/
				
				verify_builtins(&shell);
			}
			free_shell(shell);
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

	temp2 = get_name();
	path = getcwd(buf, 256);
	path = ft_substr(path, ft_strlen(getenv("HOME")), ft_strlen(path));
	temp1 = ft_strjoin(temp2, path);
	free(path);
	free(temp2);
	text = ft_strjoin(temp1, "\001\033[1;0m\002$\001\033[0m\002 ");
	free(temp1);
	return (text);
}

char	*get_name(void)
{
	char	*temp1;
	char	*temp2;
	char	*user;

	temp1 = ft_strjoin(getenv("LOGNAME"), "@");
	user = getenv("USERNAME");
	if (!user)
		user = getenv("NAME");
	temp2 = ft_strjoin(temp1, user);
	free(temp1);
	temp1 = ft_strjoin("\033[1;33m", temp2);
	free(temp2);
	temp2 = ft_strjoin(temp1, "\033[1;0m:\033[1;35m~");
	free(temp1);
	return (temp2);
}

void	inicialize(t_shell *shell)
{
	shell->line = NULL;
	shell->lex = NULL;
	shell->command = NULL;
	shell->flag = NULL;
	shell->content = NULL;
}

void	verify_builtins(t_shell *shell)
{
	if (shell->command && is_command(*shell))
	{
		printf("%s: command not found\n", shell->command);
		shell->exit_code = 127;
	}
	else
		shell->exit_code = 0;
}
