/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:20:05 by macarval          #+#    #+#             */
/*   Updated: 2023/10/08 16:21:46 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	make_shell(t_shell *shell)
{
	if (!check_void(shell->line, 0))
	{
		shell->lex = tokenization(shell);
		if (syntax_error_check(shell->lex))
			return (0);
		return (1);
	}
	return (0);
}

int	syntax_error_check(char ***lex)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	while (lex[++i] && check == 0)
	{
		if (!strcmp_mod(lex[i][1], PIPE))
			check = check_pipe(lex, i);
		else if (!strcmp_mod(lex[i][1], OPERATOR))
			check = check_operator(lex, i);
	}
	return (check);
}

int	check_pipe(char ***lex, int i)
{
	int	check;

	check = 0;
	if ((i == 0 || !lex[i + 1] || check_prev_next(lex, i)) && ++check)
		error_syntax(lex[i][0]);
	return (check);
}

int	check_operator(char ***lex, int i)
{
	int	check;

	check = 0;
	if (lex[i + 1])
	{
		check = check_prev_next(lex, i);
		if (check)
			error_syntax(lex[i + 1][0]);
	}
	if (!check && !strcmp_mod(lex[i][0], "<"))
		check = check_input_redirection(lex[i + 1]);
	else if (!check && !strcmp_mod(lex[i][0], ">"))
		check = check_output_redirection(lex[i + 1]);
	else if (!check && !strcmp_mod(lex[i][0], "<<"))
		check = check_here_document(lex[i + 1]);
	else if (!check && !strcmp_mod(lex[i][0], ">>"))
		check = check_append_redirection(lex[i + 1]);
	return (check);
}

void	error_syntax(char *text)
{
	printf("bash: syntax error near unexpected token `%s'\n",
		text);
}
