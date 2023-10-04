/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:25:32 by macarval          #+#    #+#             */
/*   Updated: 2023/10/04 14:41:25 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_prev_next(char ***lex, int i)
{
	if (!strcmp_mod(lex[i][1], PIPE))
		if (!strcmp_mod(lex[i - 1][1], PIPE) ||
			!strcmp_mod(lex[i - 1][1], OPERATOR))
			return (1);
	if (!strcmp_mod(lex[i + 1][1], PIPE) ||
		!strcmp_mod(lex[i + 1][1], OPERATOR))
		return (1);
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
	if (ft_strlen(ft_strrchr(text, '/')) == ft_strlen(text) && ++check)
		printf("bash: %s: Permission denied\n", exit);
	else
	{
		name = stat(text, &state);
		if (name && ++check)
			printf("bash: %s: No such file or directory\n", exit);
		else if (!name && !(state.st_mode & permission) && ++check)
			printf("bash: %s: Permission denied\n", exit);
	}
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

int	check_name_file(char *name)
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
