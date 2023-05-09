#include "../headers/minishell.h"
#include "../headers/redirections.h"

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	char	*ptr_2;
	int		ln1;
	int		ln2;

	ptr = s1;
	ptr_2 = s2;
	ln1 = 1;
	ln2 = 1;
	while (*++ptr)
		ln1++;
	while (*++ptr_2)
		ln2++;
	ptr = ft_calloc((ln1 + ln2) + 2, sizeof(char));
	ptr_2 = (ptr + ln1);
	ptr_2++;
	if (ptr != NULL)
	{
		while (--ln1 > -1)
			ptr[ln1] = s1[ln1];
		*(ptr_2 - 1) = '/';
		while (--ln2 > -1)
			ptr_2[ln2] = s2[ln2];
	}
	return (ptr);
}


static void	arg_validate(t_pipex *pipex, char *arg, int set, int mode)
{
	char	*arg_free;

	arg_free = NULL;
	if (arg && !*arg)
		perror_free_exit(pipex, "Invalid command! \n", 16, 1);
	while (arg && *arg)
	{
		*arg -= (mode < 0 && *arg == ' ');
		if (*arg == '\'')
		{
			while (*++arg && *(arg + 1) && *arg != '\'')
				;
			if (mode >= 0)
				arg_free = arg_trim(pipex, pipex->args[set][mode], set, mode);
		}
		if (!*++arg && mode <= -1)
			pipex->args[set] = ft_split(pipex, pipex->argv[set + 2], 31);
		if (!*arg && ++mode >= 0)
		{
			pipex->args_n[set] = pipex->count;
			free(arg_free);
			return (arg_validate(pipex, pipex->args[set][mode], set, mode));
		}
	}
}

static void	process(t_pipex *pipex, int set)
{
	int	i;

	i = -1;
	arg_validate(pipex, pipex->argv[set + 2], set, -1);
	while (pipex->paths[++i])
	{
		pipex->cmd[set] = ft_strjoin(pipex->paths[i], pipex->args[set][0]);
		if (!(access(pipex->cmd[set], X_OK)))
			break ;
		else
			free(pipex->cmd[set]);
	}
	if (!pipex->paths[i])
		pipex->cmd[set] = ft_strdup(pipex->args[set][0]);
	if (set == pipex->cmds - 1 && !pipex->paths[i])
		return (perror_free_exit(pipex, "Command not found! \n", 21, 127));
	pipex->pid = fork();
	if (!pipex->pid)
		return (childs(pipex, set));
	else if (set <= pipex->cmds - 2)
		return (process(pipex, ++set));
}

static void	pipes(t_pipex *pipex)
{
	int	i;

	i = -1;
	pipex->pipe = (int **)ft_calloc(pipex->cmds - 1, sizeof(int *));
	while (++i < pipex->cmds - 1)
	{
		pipex->pipe[i] = (int *)ft_calloc(2, sizeof(int));
		if (pipe(pipex->pipe[i]) < 0)
			return (perror_free_exit(pipex, "Pipe", 0, 1));
	}
}

void redirections(char **split, char **e)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)ft_calloc(1, sizeof(t_pipex));
	strlen(split);
    pipex->envp = e;
    pipex->args = (char ***)ft_calloc(argc - 3, sizeof(char **));
    pipex->cmd = (char **)ft_calloc(argc - 3, sizeof(char *));
	pipex->fd[0] = open(argv[1], O_RDONLY);
	pipex->fd[1] = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
    while ((*e)[0] != 'P' || (*e)[1] != 'A' || (*e)[2] != 'T' || (*e)[3] != 'H')
		e++;
	pipex->paths = split_commands(pipex, *e + 5, ':');
	pipex->paths_n = pipex->count;
	pipes(pipex);
	process(pipex, 0);
	free_all(pipex);
	waitpid(-1, NULL, 0);
    return (0);
}
