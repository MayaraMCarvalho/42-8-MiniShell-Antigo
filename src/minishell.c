/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:02:28 by macarval          #+#    #+#             */
/*   Updated: 2023/10/09 14:27:24 by macarval         ###   ########.fr       */
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
