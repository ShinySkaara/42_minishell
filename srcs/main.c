/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalonzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 12:43:04 by alalonzo          #+#    #+#             */
/*   Updated: 2019/02/26 11:56:49 by alalonzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "minishell.h"

int			sh_find_env_key(char *str, t_env *env, int mode)
{
	int		i;
	size_t	len;

	i = 0;
	while (env->env[i])
	{
		len = ft_strchrnul(env->env[i], '=') - env->env[i];
		if (ft_strncmp(str, env->env[i], len) == 0 && str[len] == mode)
			return (i);
		i++;
	}
	return (-1);
}

static void	sh_spacereplace(char *str)
{
	while (*str)
	{
		if (ft_isspace(*str))
			*str = ' ';
		str++;
	}
}

static void	sh_env_init(t_env *env)
{
	env->loop = 42;
	env->builtin[EXIT] = "exit";
	env->builtin[ECHO] = "echo";
	env->builtin[CD] = "cd";
	env->builtin[ENV] = "env";
	env->builtin[SETENV] = "setenv";
	env->builtin[UNSETENV] = "unsetenv";
	env->builtin[HELP] = "help";
	env->fun[EXIT] = sh_exit;
	env->fun[ECHO] = sh_echo;
	env->fun[CD] = sh_cd;
	env->fun[ENV] = sh_env;
	env->fun[SETENV] = sh_setenv;
	env->fun[UNSETENV] = sh_unsetenv;
	env->fun[HELP] = sh_help;
}

static void	second(char **row, t_env *env)
{
	char	**new;

	while (*row && env->loop)
	{
		if ((new = ft_strsplit(*row++, ' ')))
		{
			if (*new)
			{
				if (ft_strchr(*new, '/') == NULL)
				{
					if (sh_isbuiltin(new, env) == 0 && sh_iscmd(new, env) == 0)
						sh_error("minishell", SH_ER_NO_CMD, *new);
				}
				else
				{
					if (sh_ispath(new, env) == 0)
						sh_error("minishell", SH_ER_NO_FILE_DIR, *new);
				}
			}
			sh_array_del(new);
		}
	}
}

int			main(void)
{
	extern char	**environ;
	char		*line;
	char		**new;
	t_env		env;

	if ((env.env = sh_array_dup(environ)))
	{
		sh_env_init(&env);
		while (env.loop)
		{
			ft_putstr("->[minishell]: ");
			if ((get_next_line(0, &line)) > 0)
			{
				sh_spacereplace(line);
				if ((new = ft_strsplit(line, ';')))
				{
					second(new, &env);
					sh_array_del(new);
				}
				ft_strdel(&line);
			}
		}
		sh_array_del(env.env);
	}
	return (0);
}
