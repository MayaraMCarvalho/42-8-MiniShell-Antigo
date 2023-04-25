# include "pipex_bonus.h"

static void close_all(t_pipex *pipex, int set)
{
    int idx;

    if (!set)
        close(pipex->fd[0]);
    if (set == pipex->cmds - 1)
        close(pipex->fd[1]);
    idx = -1;
    while (++idx < pipex->cmds - 1)
    {
        close(pipex->pipe[idx][0]);
        close(pipex->pipe[idx][1]);
    }
}

void    childs(t_pipex *pipex, int set)
{
    if (!set)
    {
        if (pipex->fd[0] < 0)
		    perror_free_exit(pipex, "infile", 0, 0);
        dup2(pipex->fd[0], STDIN_FILENO);
        dup2(pipex->pipe[0][1], STDOUT_FILENO);
    }
    else if(set == pipex->cmds - 1)
    {
        if (pipex->fd[1] < 0)
		    perror_free_exit(pipex, "outfile", 0, 0);
        dup2(pipex->pipe[set - 1][0], STDIN_FILENO);
        dup2(pipex->fd[1], STDOUT_FILENO);
    }
    else
    {
        dup2(pipex->pipe[set - 1][0], STDIN_FILENO);
        dup2(pipex->pipe[set][1], STDOUT_FILENO);
    }
    close_all(pipex, set);
    execve(pipex->cmd[set], pipex->args[set], pipex->envp);
}
