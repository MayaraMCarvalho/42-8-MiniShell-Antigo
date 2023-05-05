/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:23:24 by macarval          #+#    #+#             */
/*   Updated: 2023/05/05 19:59:31 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ls(t_shell shell)
{
	DIR				*folder;
	struct dirent	*entry;
	int				files;
	int				count;

	count = 0;
	if (!ft_strncmp(shell.command, "ls", ft_strlen(shell.command)))
	{
		if (!is_flag(shell))
			return (0);
		folder = get_folder();
		files = get_number(shell);
		entry = readdir(folder);
		while (entry)
		{
			count++;
			if (shell.flag[0] == '-'
				&& ft_strchr(shell.flag, 'i'))
				printf("%li ", entry->d_ino);
			if (entry->d_name[0] != '.'
				|| ft_strchr(shell.flag, 'a'))
			{
				printf("%s", entry->d_name);
				if (ft_strchr(shell.flag, 'm')
					&& count < files)
					printf(",");
			}
			printf(" ");
			entry = readdir(folder);
		}
		printf("\n");
		closedir(folder);
		return (1);
	}
	return (0);
}

int	get_number(t_shell shell)
{
	int				count;
	DIR				*folder;
	struct dirent	*entry;

	count = 0;
	folder = get_folder();
	entry = readdir(folder);
	while (entry)
	{
		if (entry->d_name[0] != '.'
			|| ft_strchr(shell.flag, 'a'))
			count++;
		entry = readdir(folder);
	}
	closedir(folder);
	return (count);
}

DIR	*get_folder(void)
{
	DIR				*folder;
	char			buf[256];

	folder = opendir(getcwd(buf, 256));
	if (folder == NULL)
	{
		perror("Unable to read directory");
		return (0);
	}
	return (folder);
}
