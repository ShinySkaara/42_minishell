/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalonzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:04:36 by alalonzo          #+#    #+#             */
/*   Updated: 2019/02/26 12:29:08 by alalonzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	sh_compress_array(char **row, int count)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < count)
	{
		if (!row[i])
		{
			tmp = row[i];
			row[i] = row[i + 1];
			row[i + 1] = tmp;
		}
		i++;
	}
}

static int	sh_is_valid_key(char *str)
{
	char	*tmp;

	if ((tmp = ft_strchr(str, '=')) && tmp - str > 0)
	{
		tmp = str;
		while (*tmp != '=')
		{
			if (ft_isalnum(*tmp) == 0)
			{
				sh_error("setenv", SH_ER_BAD_KEY, str);
				return (0);
			}
			tmp++;
		}
		return (1);
	}
	return (0);
}

void		sh_env(char **row, t_env *env)
{
	row = env->env;
	while (*row)
		ft_putendl(*row++);
}

void		sh_setenv(char **row, t_env *env)
{
	int		i;
	int		ret;

	i = 1;
	while (row[i])
	{
		if (sh_is_valid_key(row[i]))
		{
			if ((ret = sh_find_env_key(row[i], env, '=')) > -1)
			{
				ft_strdel(&env->env[ret]);
				env->env[ret] = ft_strdup(row[i]);
			}
			else
			{
				ret = sh_array_count(env->env);
				if ((env->env = sh_array_realloc(env->env, ret + 1)))
					env->env[ret] = ft_strdup(row[i]);
			}
		}
		i++;
	}
}

void		sh_unsetenv(char **row, t_env *env)
{
	int		i;
	int		ret;
	int		count;

	i = 1;
	while (row[i])
	{
		if ((ret = sh_find_env_key(row[i], env, '\0')) > -1)
		{
			count = sh_array_count(env->env);
			ft_strdel(&env->env[ret]);
			sh_compress_array(env->env, count);
		}
		i++;
	}
}
