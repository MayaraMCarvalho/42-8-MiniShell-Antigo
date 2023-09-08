/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:01:25 by macarval          #+#    #+#             */
/*   Updated: 2023/09/08 19:15:48 by macarval         ###   ########.fr       */
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

int	c_clear(t_shell shell)
{
	if (!strcmp_mod(shell.command, "clear"))
	{
		update_(shell);
		if (!is_flag_null(shell))
			return (1);
		printf(CLEAR_SCREEN);
		return (1);
	}
	return (0);
}

int	c_exit(t_shell shell)
{
	int		control;

	control = 0;
	if (!strcmp_mod(shell.command, "exit"))
	{
		if (!is_flag_null(shell))
			return (1);
		control = 1;
		free_list(shell.env);
		free_shell(shell);
		rl_clear_history();
	}
	return (control);
}
