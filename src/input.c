/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 05:06:45 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/21 20:16:52 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*read_line(char **envp)
{
	char	*line;

	line = NULL;
	line = readline("minishell$> ");
	if (!line)
	{
		ft_freematrix(envp);
		rl_clear_history();
		exit(0);
	}
	return (line);
}

int	check_input(char *line)
{
	int	status;

	if (!*line)
	{
		free(line);
		return (0);
	}
	status = 2;
	if (!*line)
		return (0);
	if (!validate_redirections(line) || !validate_pipes(line))
	{
		printf("minishell: syntax error\n");
		free(line);
		exit_status(&status);
		return (0);
	}
	return (1);
}

int	validate_pipes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] == '|')
		{
			if (i == 0)
				return (0);
			if (!line[i + 1] || line[i + 1] == '|')
				return (0);
			i++;
			while (line[i] && line[i] == ' ')
				i++;
			if (line[i] == '|')
				return (0);
		}
		else
			while (line[i] && line[i] != '|' && line[i] != ' ')
				i++;
	}
	return (1);
}

int	validate_redirections(char *line)
{
	int		i;
	char	current_redirection;

	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] != '>' && line[i] != '<')
			i++;
		if (line[i] == '>' || line[i] == '<')
		{
			current_redirection = line[i];
			if (i != 0 && line[i - 1] != ' ' && line[i
					- 1] != current_redirection && line[i - 1] != '|')
				return (0);
			if (line[i + 1] == current_redirection)
				i++;
			i++;
			while (line[i] && line[i] == ' ')
				i++;
			if (line[i] == '>' || line[i] == '<' || !line[i])
				return (0);
		}
	}
	return (1);
}