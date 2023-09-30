/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:58:03 by macarval          #+#    #+#             */
/*   Updated: 2023/09/29 13:00:20 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	syntax_error_check(char ***lex)
{
	int		i;
	int		check;

	i = -1;
	check = 0;
	while (lex[++i] && check == 0)
	{
		if (!strcmp_mod(lex[i][1], PIPE))
		{
			if ((i == 0 || !lex[i + 1]
				|| check_prev_next(lex, i)) && ++check)
				error_syntax(lex[i][0]);
		}
		else if (!strcmp_mod(lex[i][1], OPERATOR))
		{
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
			// else if (!strcmp_mod(lex[i][0], "<<"))
			// 	check = check_here_document(lex, i);
			// else if (!strcmp_mod(lex[i][0], ">>"))
			// 	check = check_append_redirection(lex, i);
		}
	}
	return (check);
}

int	check_prev_next(char ***lex, int i)
{
	if (!strcmp_mod(lex[i][1], PIPE))
		if (!strcmp_mod(lex[i - 1][1], PIPE) ||
			!strcmp_mod(lex[i - 1][1], OPERATOR))
			return (1);
	if	(!strcmp_mod(lex[i + 1][1], PIPE) ||
		!strcmp_mod(lex[i + 1][1], OPERATOR))
		return (1);
	return (0);
}

int	check_input_redirection(char **text)
{
	int			check;

	check = 0;
	if (!text && ++check)
		error_syntax("newline");
	else
		check = check_permission(text[0], S_IRUSR, text[0]);
	return (check);
}

int	check_output_redirection(char **text)
{
	int			check;

	check = 0;
	if (!text && ++check)
		error_syntax("newline");
	else if (validate_name_file(text[0]))
		return (1);
	else
	{
		if (text[0][ft_strlen(text[0]) - 1] == '/' && ++check)
			printf("bash: %s: Is a directory\n", text[0]);
		else
		{
			check = check_folder(text[0]);
			if (!check)
				check = check_file(text[0]);
		}
	}
	return (check);
}

int	validate_name_file(char *name)
{
	int		i;
	char	letter[2];

	i = -1;
	letter[0] = '\0';
	letter[1] = '\0';
	while (name && name[++i] && letter[0] == '\0')
	{
		if (ft_strchr("()|", name[i]))
			letter[0] = name[i];
	}
	if (letter[0])
	{
		error_syntax(letter);
		return (1);
	}
	return (0);
}

int	check_folder(char *text)
{
	char	*name_folder;
	int		check;

	check = 0;
	name_folder = ft_strrchr(text, '/');
	if (name_folder)
	{
		name_folder = ft_substr(text, 0, ft_strlen(text)
				- ft_strlen(name_folder) + 1);
		if (name_folder)
		{
			check = check_permission(name_folder, S_IWUSR, text);
			free(name_folder);
		}
	}
	return (check);
}

int	check_permission(char *text, int permission, char *exit)
{
	int			check;
	struct stat	state;
	int			name;

	check = 0;
	name = stat(text, &state);
	if (name && ++check)
		printf("bash: %s: No such file or directory\n", exit);
	else if (!name && !(state.st_mode & permission) && ++check)
		printf("bash: %s: Permission denied\n", exit);
	return (check);
}

int	check_file(char *text)
{
	int			tam;
	int			check;
	struct stat	state;

	check = 0;
	tam = ft_strlen(ft_strrchr(text, '/'));
	if ((tam > 256 || (tam == 0 && ft_strlen(text) > 255)) && ++check)
		printf("bash: %s: File name too long\n", text);
	else if (!stat(text, &state)
		&& !(state.st_mode & S_IWUSR) && ++check)
		printf("bash: %s: Permission denied\n", text);
	return (check);
}

void	error_syntax(char *text)
{
	printf("bash: syntax error near unexpected token `%s'\n",
		text);
}
