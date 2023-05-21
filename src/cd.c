/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:02:42 by macarval          #+#    #+#             */
/*   Updated: 2023/05/20 23:03:27 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// Passar norminette

int	c_cd(t_shell shell)
{
	//char	buf[256];

	if (!strcmp_mod(shell.command, "cd"))
	{
		if (!is_flag_null(shell))
			return (1);
		if (!shell.content)
			shell.content = getenv("HOME");
		else if (!strcmp_mod(shell.content, "-"))
		{
			shell.content = getenv("OLDPWD"); // substituir por consulta na lista env
			printf("%s\n", shell.content);
		}
		if (chdir(shell.content) != 0)
			printf("bash: cd: %s: No such file or directory\n", shell.content);
		else
		{
			rl_redisplay();

			// Alterar para atualizar variaveis de ambiente
				if (shell.env)
				{}
			//

			/*
			// setenvp(shell, "OLDPWD", getenv("PWD")); // substituir por consulta na lista env
			// printf("oldpwd: %s\n\n", getenv("OLDPWD")); // substituir por consulta na lista env
			// printf("env: %s\n", shell.envp[31]);
			// setenvp(shell, "PWD", getcwd(buf, 256)); // substituir por consulta na lista env
			// printf("pwd: %s\n", getenv("PWD")); // substituir por consulta na lista env
			// printf("env: %s\n", shell.envp[5]);
			*/
		}
		return (1);
	}
	return (0);
}

// void	setenvp(t_shell shell, char *var, char *content)
// {
// 	int		i;
// 	char	*temp;

// 	i = -1;
// 	while (shell.envp[++i] != NULL)
// 	{
// 		if (!strcmp_mod(shell.envp[i], var)
// 			&& shell.envp[i][ft_strlen(var)] == '=')
// 			break ;
// 	}
// 	if (shell.envp[i])
// 	{
// 		temp = ft_strjoin(var, "=");
// 		temp = ft_strjoin(temp, content);
// 		shell.envp[i] = temp;
// 	}
// 	/*
// 	// printf("env: %i %s\n", i, shell.envp[i]);
// 	// printf("var: %s\n", getenv(var));
// 	*/
// }
