/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 05:13:48 by dinunes-          #+#    #+#             */
/*   Updated: 2023/07/31 11:08:12 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;

	line = 0;
	(void)ac;
	(void)av;
	(void)envp;
	signal(2, handle_sigint);
	while (1)
	{
		line = readline("minishell~$ ");
		if (line == NULL)
			exit(0);
		parsing(line, envp);
		free(line);
	}
}
