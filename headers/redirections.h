#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>

typedef struct s_pipex
{
    char    ***args;
    char    **argv;
    char    **cmd;
    char    **envp;
    char    **paths;
    int     **pipe;
    int     args_n[2];
    int     count;
    int     fd[2];
    int     cmds;
    int     paths_n;
    pid_t   pid;
}   t_pipex;

char	**split_commands(t_pipex *pipex, char *s, char c);

char    *arg_trim(t_pipex *pipex, char *arg, int set, int mode);

char	*ft_strdup(const char *s);

void	*ft_calloc(size_t nmemb, size_t size);

void    childs(t_pipex *pipex, int set);

void    free_all(t_pipex *pipex);

void    perror_free_exit(t_pipex *pipex, char *error, int len, int err);

#endif