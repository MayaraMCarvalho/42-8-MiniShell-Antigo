/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:01:25 by macarval          #+#    #+#             */
/*   Updated: 2023/10/03 20:06:28 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_shell(t_shell shell)
{
	free(shell.line);
	if (shell.command)
		free(shell.command);
	if (shell.flag)
		free(shell.flag);
	if (shell.content)
		free(shell.content);
	if (shell.lex)
		free_double(&shell.lex);
}

void	free_array(char ***array)
{
	int		i;
	char	**temp;

	i = -1;
	temp = *array;
	while (temp[++i])
		free(temp[i]);
	free(*array);
}

void	free_double(char ****array)
{
	int		i;
	char	***temp;

	i = -1;
	temp = *array;
	while (temp[++i])
	{
		free(temp[i][0]);
		free(temp[i][1]);
		free(temp[i]);
	}
	free(*array);
}

void	free_list(t_lst *list)
{
	t_lst	*temp;
	t_lst	*next;

	temp = list;
	while (temp != NULL)
	{
		free(temp->var);
		if (temp->msg)
			free(temp->msg);
		next = temp->next;
		free(temp);
		temp = next;
	}
}
