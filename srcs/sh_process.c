/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalonzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 10:24:04 by alalonzo          #+#    #+#             */
/*   Updated: 2019/02/26 12:27:49 by alalonzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	sh_run(char *cmd, char **row, t_env *env)
{
	int	pid;
	int	ret;

	pid = fork();
	if (pid < 0)
	{
		sh_error("minishell", SH_ER_NO_FORK, NULL);
	}
	else if (pid == 0)
	{
		if (execve(cmd, row, env->env) < 0)
		{
			sh_error("minishell", SH_ER_NO_EXEC, NULL);
		}
	}
	else
	{
		wait(&ret);
	}
	return (1);
}

static char	*sh_combinator(char *str, char **row)
{
	char	*new;
	size_t	len_a;
	size_t	len_b;

	while (*row)
	{
		len_a = ft_strlen(*row);
		len_b = ft_strlen(str);
		if ((new = (char *)malloc(sizeof(char) * (len_a + len_b + 2))))
		{
			ft_strncpy(new, *row, len_a);
			ft_strncpy(new + 1 + len_a, str, len_b);
			new[len_a] = '/';
			new[len_a + len_b + 1] = '\0';
			if (access(new, F_OK) == 0)
				return (new);
			free(new);
		}
		row++;
	}
	return (NULL);
}

int			sh_isbuiltin(char **row, t_env *env)
{
	int		i;

	i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (ft_strcmp(env->builtin[i], *row) == 0)
		{
			(*env->fun[i])(row, env);
			return (1);
		}
		i++;
	}
	return (0);
}

int			sh_iscmd(char **row, t_env *env)
{
	int		ret;
	char	*tmp;
	char	**new;

	if ((ret = sh_find_env_key("PATH", env, '\0')) > -1)
	{
		tmp = ft_strchr(env->env[ret], '=') + 1;
		if ((new = ft_strsplit(tmp, ':')))
		{
			ret = 0;
			if ((tmp = sh_combinator(*row, new)))
			{
				if (sh_access(tmp, "minishell"))
				{
					ret = sh_run(tmp, row, env);
				}
				free(tmp);
			}
			sh_array_del(new);
			return (ret);
		}
	}
	return (0);
}

int			sh_ispath(char **row, t_env *env)
{
	if (access(*row, F_OK) == 0)
	{
		if (sh_access(*row, "minishell"))
		{
			sh_run(row[0], row, env);
		}
		return (1);
	}
	return (0);
}
