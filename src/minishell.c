/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:02:28 by macarval          #+#    #+#             */
/*   Updated: 2023/05/27 14:47:07 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/*
	Teste de funções
	char	*name;
	char	*bp;
	int		height;
	int		width;

	name = getenv("TERM");
	bp = malloc(sizeof(*bp));
	if (tgetent(bp, name) < 0)
	{
		fprintf(stderr, "Erro ao carregar as capacidades do terminal.\n");
		return 1;
	}
	height = tgetnum ("li");
	width = tgetnum ("co");
	printf("H : %d\nL : %d\n", height, width);

    if (tputs("Hello, world!\n", 1, putchar) == -1) {
        fprintf(stderr, "Erro ao enviar a sequência para o terminal.\n");
        return 1;
    }
	free (bp);
	exit(0);
*/

// Passar norminette

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	char		*text;

	if (argc && argv)
	{
	}
	shell.env = make_list(envp);
	while (1)
	{
		text = make_text();
		shell.line = readline(text);
		free(text);
		if (shell.line[0] != '\0')
		{
			add_history (shell.line);
			make_shell(&shell, shell.line);
			if (shell.command && is_command(shell))
				printf("%s: command not found\n", shell.command);
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
	shell->command = NULL;
	shell->flag = NULL;
	shell->content = NULL;
}
