/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:00:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/16 22:54:40 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	echo(char **cmd)
{
	int	flag;

	flag = 0;
	if (*cmd && ft_strncmp(*cmd, "-n", 2) == 0)
	{
		cmd++;
		flag = 1;
	}
	while (*cmd)
	{
		printf("%s", *cmd++);
		if (*cmd)
			printf(" ");
	}
	if (!flag)
		printf("\n");
	exit(0);
}

void	call_chdir(char *cmd, int *status)
{
	if (chdir(cmd))
	{
		printf("Error: %s\n", strerror(errno));
		*status = 1;
	}
}

void	cd(char **cmd, char ***envp)
{
	int			status;
	char		*current_pwd;
	static char	*old_pwd;
	char		*tmp;

	status = 0;
	current_pwd = getcwd(NULL, 0);
	old_pwd = search_env(envp, "OLDPWD");
	if (!*cmd || !ft_strncmp(*cmd, "~", 2))
		call_chdir((search_env(envp, "HOME")), &status);
	else if (!ft_strncmp(*cmd, "~/", 2))
	{
		tmp = ft_strjoin(search_env(envp, "HOME"), *cmd + 1);
		call_chdir(tmp, &status);
		free(tmp);
	}
	else if (!ft_strncmp(*cmd, "-", 2) && old_pwd)
		call_chdir(old_pwd, &status);
	else
		call_chdir(*cmd, &status);
	old_pwd = ft_strjoin("OLDPWD=", current_pwd);
	*envp = env_remove(envp, "OLDPWD");
	*envp = env_add(envp, old_pwd);
	free_strings(current_pwd, old_pwd);
	exit_status(&status);
}
