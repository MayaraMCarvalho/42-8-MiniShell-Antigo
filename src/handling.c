/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:20:05 by macarval          #+#    #+#             */
/*   Updated: 2023/09/24 21:37:45 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	make_shell(t_shell *shell)
{
	char	**token;
	char	***lex;

	token = tokenization(shell);
	lex = lexer(token);
	if (!lex)
		return ;
	verify_expasion(lex, shell);
	/* retirar */
	int i = -1;
	while (lex[++i])
		printf("%-10s %-10s\n", lex[i][1], lex[i][0]);
	printf("\n");
	/**/
	// Fazer o parsing correto;
	if (token[0] && !ft_strchr(token[0], '='))
	{
		shell->command = ft_strdup(token[0]);
		put_token(shell, token);
	}
	else
	{
		shell->command = ft_strdup(shell->line);
		shell->content = NULL;
	}
	free_array(&token);
	free_double(&lex);
}

void	put_token(t_shell *shell, char **token)
{
	int		tam_command;

	tam_command = ft_strlen(shell->command);
	if (token[1])
	{
		if (token[1][0] == '-'
			&& (strcmp_mod(shell->command, "echo")
			|| (!strcmp_mod(shell->command, "echo")
			&& !verify_flags(token[1] + 1, "n"))))
			shell->flag = ft_strdup(token[1]);
		else
			shell->content = ft_substr(shell->line, tam_command + 1,
					ft_strlen(shell->line));
		if (!shell->content && token[2])
		{
			if (shell->content)
				free(shell->content);
			if (shell->flag)
				shell->content = ft_substr(shell->line, tam_command
						+ ft_strlen(shell->flag) + 2, ft_strlen(shell->line));
			else
				shell->content = ft_substr(shell->line, tam_command + 1,
						ft_strlen(shell->line));
		}
	}
}

void	verify_expasion(char	***lex, t_shell *shell)
{
	int		i;
	char	*init;
	char	*var;
	char	*content;

	i = 0;
	while (lex[i])
	{
		if (!strcmp_mod(lex[i][1], CONTENT) && ft_strchr(lex[i][0], '$'))
		{
			init = strchr_rev(lex[i][0], '$');
			var = get_var(ft_strchr(lex[i][0], '$'), shell);
			if (var)
				content = ft_strjoin(init, var);
			else
				content = ft_strdup(init);
			free(var);
			free(lex[i][0]);
			lex[i][0] = ft_strdup(content);
			free(content);
			free(init);
		}
		i++;
	}
}

char	*get_var(char *token, t_shell *shell)
{
	t_lst	*node;
	char	*final;
	char	*var;
	int		i;

	i = 1;
	while (ft_isalnum(token[i]))
		i++;
	final = ft_substr(token, i, ft_strlen(token) - i);
	var = ft_substr(token, 0, i);
	node = find_arg(*shell, ++var);
	free(--var);
	if (node && node->msg)
		var = ft_strjoin(node->msg, final);
	else
		var = ft_strdup(final);
	free(final);
	return (var);
}
