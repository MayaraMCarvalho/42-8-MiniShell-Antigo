/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:02:42 by macarval          #+#    #+#             */
/*   Updated: 2023/05/27 17:23:30 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	c_cd(t_shell shell)
{
	t_lst	*var;
	char	*oldpwd;
	char	buf[256];

	if (!strcmp_mod(shell.command, "cd"))
	{
		if (!is_flag_null(shell))
			return (1);
		if (!shell.content && !shell.flag)
			shell.content = getenv("HOME");
		else if (!strcmp_mod(shell.flag, "-"))
		{
			var = find_arg(shell, "OLDPWD");
			shell.content = var->msg;
			printf("%s\n", shell.content);
		}
		var = find_arg(shell, "PWD");
		oldpwd = var->msg;
		if (chdir(shell.content) != 0)
			printf("bash: cd: %s: No such file or directory\n", shell.content);
		else
		{
			rl_redisplay();
			update_var(shell, "OLDPWD", oldpwd);
			update_var(shell, "PWD", getcwd(buf, 256));
		}
		return (1);
	}
	return (0);
}

void	update_var(t_shell shell, char *name, char *value)
{
	t_lst	*lst;

	lst = find_arg(shell, name);
	if (lst)
	{
		free(lst->msg);
		lst->msg = ft_strdup(value);
	}
}
