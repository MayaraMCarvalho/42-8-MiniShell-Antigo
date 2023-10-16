/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:36:22 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 11:56:58 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	syntax_error_check(char ***lex, t_shell *shell)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	while (lex[++i] && check == 0)
	{
		if (!strcmp_mod(lex[i][1], PIPE))
			check = check_pipe(lex, i, shell);
		else if (!strcmp_mod(lex[i][1], OPERATOR))
		{
			check = check_operator(lex, i, shell);
			id_redirection(lex, i);
		}
	}
	return (check);
}

int	check_pipe(char ***lex, int i, t_shell *shell)
{
	int	check;

	check = 0;
	if ((i == 0 || !lex[i + 1] || check_prev_next(lex, i)) && ++check)
		error_syntax(lex[i][0], shell);
	return (check);
}

int	check_operator(char ***lex, int i, t_shell *shell)
{
	int	check;

	check = 0;
	if (lex[i + 1])
	{
		check = check_prev_next(lex, i);
		if (check)
			error_syntax(lex[i + 1][0], shell);
	}
	if (!check && !strcmp_mod(lex[i][0], "<"))
		check = check_input_redirection(lex[i + 1], shell);
	else if (!check && !strcmp_mod(lex[i][0], ">"))
		check = check_output_redirection(lex[i + 1], shell);
	else if (!check && !strcmp_mod(lex[i][0], "<<"))
		check = check_here_document(lex[i + 1], shell);
	else if (!check && !strcmp_mod(lex[i][0], ">>"))
		check = check_append_redirection(lex[i + 1], shell);
	return (check);
}

void	error_syntax(char *text, t_shell *shell)
{
	printf("bash: syntax error near unexpected token `%s'\n",
		text);
	if (shell->env)
		shell->exit_code = 2;
}
