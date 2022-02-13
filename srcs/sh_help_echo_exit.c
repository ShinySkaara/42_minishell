/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_help_echo_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalonzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:27:55 by alalonzo          #+#    #+#             */
/*   Updated: 2019/02/26 12:21:46 by alalonzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	sh_help(char **row, t_env *env)
{
	(void)row;
	(void)env;
	ft_putendl("*************************************************************");
	ft_putendl("**                        MINISHELL                        **");
	ft_putendl("*************************************************************");
	ft_putendl("** builtins disponibles:                                   **");
	ft_putendl("** - exit                                                  **");
	ft_putendl("** - echo                                                  **");
	ft_putendl("** - cd                                                    **");
	ft_putendl("** - help                                                  **");
	ft_putendl("** - env                                                   **");
	ft_putendl("** - setenv                                                **");
	ft_putendl("** - unsetenv                                              **");
	ft_putendl("*************************************************************");
}

void	sh_echo(char **row, t_env *env)
{
	int		i;
	int		ret;
	char	*tmp;

	i = 1;
	while (row[i])
	{
		tmp = ft_strcmp(row[i], "~") == 0 ? "$HOME" : row[i];
		if (tmp[0] == '$')
		{
			if ((ret = sh_find_env_key(tmp + 1, env, '\0')) > -1)
				tmp = ft_strchr(env->env[ret], '=') + 1;
			else
				tmp = NULL;
		}
		if (tmp)
		{
			ft_putstr(tmp);
			ft_putchar(' ');
		}
		i++;
	}
	ft_putchar('\n');
}

void	sh_exit(char **row, t_env *env)
{
	(void)row;
	env->loop = 0;
}
