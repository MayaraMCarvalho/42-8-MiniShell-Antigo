/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:02:28 by macarval          #+#    #+#             */
/*   Updated: 2023/04/07 14:55:31 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/redirections.h"

char *is_spaces(char *line, char *spaces)
{
	while (*spaces)
	{
		if (*line != *spaces)
			spaces++;
		else if (*line == *spaces)
		{
			line++;
			spaces = SPACES;
		}
	}
	return (line); 
}

void here_doc_exec(int *fd, char *delimiter, int line_diff)
{
	char *user_input;
	int user_input_len;

	user_input = readline("> ");
	while (ft_strncmp(delimiter, user_input, line_diff))
	{
		user_input_len = ft_strlen(user_input);
		if (!write(fd[0], user_input, user_input_len))
			user_input = readline("> ");
	}
}

char *here_doc_setup(t_block *current_block, char *line)
{
	char *doc_name;
	char *line_tmp;
	int  line_diff;
	char *delimiter;

	doc_name = current_block->heredoc_name;
	current_block->fd[0] = open(doc_name, O_CREAT | O_RDWR, 0644);
	line = is_spaces(line, SPACES);
	line_tmp = line;
	while (line_tmp != is_spaces(line_tmp, SPACES))
		line_tmp++;
	line_diff = line_tmp - line;
	delimiter = (char *)ft_calloc(line_diff, sizeof(char));
	delimiter = ft_substr(line, 0, line_diff);
	here_doc_exec(&current_block->fd[0], delimiter, line_diff);
	return (line + line_diff);
}

char *special_cases(t_block *current_block, char *line)
{
		if (*line == '<' && *++line == '<')
			return (here_doc_setup(current_block, line + 1));
		else if (*line == '>')
		{
			current_block->io1_type = 1;
			if (*++line == '>')
			{
				current_block->io1_type = 2;
				line++;
			}
		}
		if (*line == '|' && line++)
		{
			if(!pipe(current_block->pipe))
				current_block->set = 0;
		}
		else
			current_block->set = 2;
	return (line);
}

char *is_special(t_block *current_block, char *line, char *specials)
{
	while (*specials)
	{
		if (*line != *specials)
			specials++;
		else if (*line == *specials)
		{
			if (current_block->set == 2)
				return("error token");
			return (special_cases(current_block, line));
		}
	}
	return (line); 
}


char *is_command1(char *line)
{
	return(line);
}

char *heredoc_name_setup(t_block *current_block, char *heredoc_name)
{
	if (!heredoc_name)
		heredoc_name = HEREDOCNAME;
	else if (heredoc_name)
	{
		if (heredoc_name[5] == '9')
		{
			heredoc_name[5] = '0';
			heredoc_name[4] += 1;
		}
		heredoc_name[5] += 1;
	}
	current_block->heredoc_name = heredoc_name;
	return (heredoc_name);
}

void process(t_block *current_block, char *line)
{
	char *heredoc_name;

	while (line && *line)
	{
		if (!current_block || (current_block && !current_block->set))
		{
			current_block = new_block_on_pipe_list(current_block);
			heredoc_name = heredoc_name_setup(current_block, heredoc_name);
		}
		line = is_spaces(line, SPACES);
		line = is_special(current_block, line, SPECIALS);
		// line = is_file(current_block, line);
		// line = is_command1(current_block, line);
	}
}

char	*make_text(void)
{
	char	*text;
	char	buf[256];
	char	*path;
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(getenv("LOGNAME"), "@");
	temp2 = ft_strjoin(temp1, getenv("NAME"));
	free(temp1);
	temp1 = ft_strjoin("\033[1;33m", temp2);
	free(temp2);
	temp2 = ft_strjoin(temp1, "\033[1;0m:\033[1;35m~");
	free(temp1);
	path = getcwd(buf, 256);
	path = ft_substr(path, ft_strlen(getenv("HOME")), ft_strlen(path));
	temp1 = ft_strjoin(temp2, path);
	free(path);
	free(temp2);
	text = ft_strjoin(temp1, "\001\033[1;0m\002$\001\033[0m\002 ");
	free(temp1);
	return (text);
}

void minishell(t_shell *shell)
{
	char *line;
	while (1)
	{
		printf("\033[1;35m");
		line = readline(make_text());
		if (shell->line)
		{
			add_history(shell->line);
			process(shell->pipelist, line);
		}
	}
}
