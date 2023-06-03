/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:02:42 by macarval          #+#    #+#             */
/*   Updated: 2023/06/03 17:23:17 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	c_cd(t_shell shell)
{
	t_lst	*var;

	if (!strcmp_mod(shell.command, "cd"))
	{
		update_(shell);
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
		exe_cd(shell);
		return (1);
	}
	return (0);
}

void	exe_cd(t_shell shell)
{
	t_lst	*var;
	char	*oldpwd;
	char	buf[256];

	var = find_arg(shell, "PWD");
	oldpwd = var->msg;
	if (chdir(shell.content) != 0)
		printf("bash: cd: %s: No such file or directory\n", shell.content);
	else
	{
		update_var(shell, "OLDPWD", oldpwd);
		update_var(shell, "PWD", getcwd(buf, 256));
	}
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
