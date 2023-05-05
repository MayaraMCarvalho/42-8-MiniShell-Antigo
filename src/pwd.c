/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:35:46 by macarval          #+#    #+#             */
/*   Updated: 2023/05/05 16:51:23 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	pwd(t_shell shell)
{
	char	buf[256];

	if (!ft_strncmp(shell.command, "pwd", ft_strlen(shell.command)))
	{
		if (!is_flag_null(shell))
			return (1);
		printf("%s\n", getcwd(buf, 256));
		return (1);
	}
	return (0);
}
