/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:02:42 by macarval          #+#    #+#             */
/*   Updated: 2023/05/05 16:43:51 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	cd(t_shell shell)
{
	//char	buf[256];

	if (!ft_strncmp(shell.command, "cd", ft_strlen(shell.command)))
	{
		if (!is_flag_null(shell))
			return (1);
		if (!shell.content)
			shell.content = getenv("HOME");
		else if (!ft_strncmp(shell.content, "-", ft_strlen(shell.content)))
		{
			shell.content = getenv("OLDPWD");
			printf("%s\n", shell.content);
		}
		if (chdir(shell.content) != 0)
			printf("bash: cd: %s: No such file or directory\n", shell.content);
		else
		{
			/*
			// setenvp(shell, "OLDPWD", getenv("PWD"));
			// printf("oldpwd: %s\n\n", getenv("OLDPWD"));
			// printf("env: %s\n", shell.envp[31]);
			// setenvp(shell, "PWD", getcwd(buf, 256));
			// printf("pwd: %s\n", getenv("PWD"));
			// printf("env: %s\n", shell.envp[5]);
			*/
		}
		return (1);
	}
	return (0);
}

void	setenvp(t_shell shell, char *var, char *content)
{
	int		i;
	int		tam;
	char	*temp;

	i = -1;
	tam = ft_strlen(var);
	while (shell.envp[++i] != NULL)
	{
		if (!ft_strncmp(shell.envp[i], var, tam)
			&& shell.envp[i][tam] == '=')
			break ;
	}
	if (shell.envp[i])
	{
		temp = ft_strjoin(var, "=");
		temp = ft_strjoin(temp, content);
		shell.envp[i] = temp;
	}
	/*
	// printf("env: %i %s\n", i, shell.envp[i]);
	// printf("var: %s\n", getenv(var));
	*/
}
