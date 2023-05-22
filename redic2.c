/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redic2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:25:47 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/22 20:03:20 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

//CHECKPOINT

/**
 * @brief Here we write to the pipe the content of here_doc
 * the parent will read from the pipe and any command will be executed
 * @param i 
 * @param eof 
 * @return char* 
 */
int *delimiter(char *eof, int *fd)
{
	char	*line;
	
	printf(BLUE"\ndelimiter\n"RST_CLR);
	//dup2(fd[1], STDOUT_FILENO);
	while (42)
		{
			line = readline("> ");
			if (ft_strncmp(line, eof, ft_strlen(line)) == 0 && ft_strlen(line) == ft_strlen(eof))
			{
				free(line);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		close(fd[1]);
	return (0);
}

/**
 * @brief Creates a sub process that will write to the pipe the content of here_doc
 * the parent will read from the pipe and any command will have
 * the content of the pipe as input.
 * The here_doc will be read only if there is no more infiles
 * @param eof 
 */
void	ft_here_doc(char *eof, int i)
{
	int		pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		delimiter(eof, fd);
		exit (0);
	}
	else
	{
		waitpid (pid, NULL, 0);
		close (fd[1]);
		if (g_data.infiles[i + 1] == NULL)
		dup2(fd[0], STDIN_FILENO);
		close (fd[0]);
	}
}

/**
 * @brief Analizes infiles array
 * open all the infiles and save the 
 * last fd in g_data.fd_in
 * checks if there is a here_doc call when 
 * there are "<<" in the infile name
 * adn calls the ft_here_doc function
 * @return int 
 */
int	infiles_doc(void)
{
	int		i; 
	char	*eof; //MEMORY LEAK
	
	i = 0;
	printf(YELLOW"\ninfiles"RST_CLR".\n");
	ft_printf_arr(g_data.infiles);
	while (g_data.infiles[i])
	{
		if (g_data.infiles[i][1] == '<' && g_data.infiles[i][2] != '<') 
		{
			printf(BLUE"\nhere_doc\n"RST_CLR);
			eof = ft_strtrim(g_data.infiles[i], "< ");
			ft_here_doc(eof, i);
			g_data.flags.here_doc = 1;
			if (g_data.infiles[i + 1] == NULL)
				break ;
			else
				free(eof);
		}
		ft_open(i);
		i++;
	}
	// if (eof) //MEMORY LEAK WH
	// 	free(eof);
	return (0);
}

int	ft_error_in(char *s1, char *s2, char *s3, int ret)
{
	ft_putstr_fd(s1, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
	exit (ret);
}

/**
 * @brief Checks if all infiles are valid, only with one '<'
 * yes, it can be done with access, but we get the same result.
 * @return int 
 */
int	check_infiles(void)
{
	int		i;
	int		fd;
	char	*aux;

	i = 0;
	printf(YELLOW"\ncheck_infiles"RST_CLR".\n");
	while (g_data.infiles[i])
	{
		while (g_data.infiles[i] != NULL && g_data.infiles[i][1] == '<')
		{
			printf("g_data.infiles[%d] = '%s'\n", i, g_data.infiles[i]);
			i++;
		}
		printf("\nIM HERE\n");
		if (g_data.infiles[i] == NULL)
			break ;
		aux = ft_strtrim(g_data.infiles[i], "< ");
		fd = open(aux, O_RDONLY);
		if (fd == -1)
		{
			//free(aux);
			return (ft_error_in(RED"\nminishell: ", (g_data.infiles[i] + 1), \
			": No such file or directory\n"RST_CLR, 1));
		}
		close(fd);
		//free(aux);
		i++;
	}
	printf("\ncheck_infiles done\n");
	return (0);
}

/**
 * @brief Analizes infiles and outfiles
 * creates and reads the respective files
 * if there are more than one infile or outfile 
 * it will create all but only read the last one
 * and the last one will be the outfile for the dup2
 * @return int 
 */
int	analyze_redic(void)
{
	//printf("\nanalize_redic\n");
	if (g_data.infiles)
	{
		infiles_doc();
		check_infiles();
	}
	return (0);
}