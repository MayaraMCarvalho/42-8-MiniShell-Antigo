#include "../headers/redirections.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	int		result;
	void	*s;

	result = nmemb * size;
	if (result == 0 || result / size != nmemb)
		return (NULL);
	ptr = (void *)malloc(result);
	s = ptr;
	while (result--)
		*(unsigned char *)s++ = 0;
	return (ptr);
}

void	free_all(t_pipex *pipex)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while (i[0] < pipex->paths_n)
	{
		if (i[0] < pipex->cmds)
		{
			while (i[1] < pipex->args_n[i[0]])
				free(pipex->args[i[0]][i[1]++]);
			if (i[0] < pipex->cmds - 1)
				free(pipex->pipe[i[0]]);		
			free(pipex->cmd[i[0]]);
			free(pipex->args[i[0]]);
		}
		free(pipex->paths[i[0]]);
		i[1] = 0;
		i[0]++;
	}
	free(pipex->paths);
	free(pipex->pipe);
	free(pipex->cmd);
	free(pipex->args);
	free(pipex);
}

void	perror_free_exit(t_pipex *pipex, char *error, int len, int err)
{
	if (pipex->args[0])
		free_all(pipex);
	else
		free(pipex);
	if (!len)
		perror(error);
	if (len > 0)
		write(2, error, len);
	if (len >= 0)
		exit(err);
}

char	*ft_strdup(const char *s)
{
	char	*cache;
	char	*ptr;
	char	*p;
	int		len;

	len = 1;
	p = (char *)s;
	while (*++p)
		len++;
	cache = ft_calloc(len + 1, sizeof(char));
	ptr = cache;
	while (*s)
		*cache++ = *(char *)s++;
	return (ptr);
}

char	*arg_trim(t_pipex *pipex, char *arg, int set, int mode)
{
	char	*ptr;
	int		len;

	len = 1;
	ptr = arg;
	while (*++ptr)
		len++;
	pipex->args[set][mode] = (char *)ft_calloc(len - 1, sizeof(char));
	--len;
	while (--len)
		pipex->args[set][mode][len - 1] = arg [len];
	return (arg);
}
