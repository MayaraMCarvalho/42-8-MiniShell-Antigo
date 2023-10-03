/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:58:03 by macarval          #+#    #+#             */
/*   Updated: 2023/10/03 20:34:48 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_input_redirection(char **text)
{
	int	check;

	check = 0;
	if (!text && ++check)
		error_syntax("newline");
	else
		check = check_permission(text[0], S_IRUSR, text[0]);
	return (check);
}

int	check_output_redirection(char **text)
{
	int	check;

	check = 0;
	if (!text && ++check)
		error_syntax("newline");
	else if (check_name_file(text[0]))
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

int	check_here_document(char **text)
{
	int			check;

	check = 0;
	if (!text && ++check)
		error_syntax("newline");
	return (check);
}

int	check_append_redirection(char **text)
{
	int			check;
	struct stat	state;

	check = 0;
	if (!text && ++check)
		error_syntax("newline");
	else if (text[0][ft_strlen(text[0]) - 1] == '/' && ++check)
		printf("bash: %s: Is a directory\n", text[0]);
	else
	{
		if (((ft_strlen(ft_strrchr(text[0], '/')) == ft_strlen(text[0]))
				|| (!stat(text[0], &state) && !(state.st_mode & S_IWUSR)))
			&& ++check)
			printf("bash: %s: Permission denied\n", text[0]);
		else
			check = check_folder(text[0]);
	}
	return (check);
}
