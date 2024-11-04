/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion_01.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:17:01 by antfonse          #+#    #+#             */
/*   Updated: 2024/11/03 21:08:08 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	putnbr_recursive(int nb, char **nb_char)
{
	if ((nb / 10) != 0)
		putnbr_recursive((nb / 10), nb_char);
	**nb_char = (nb % 10) + '0';
	*nb_char = *nb_char + 1;
}

// GET RETURN CODE
static char	*get_return_code(t_data *ms_data, char *start, char **str)
{
	char	ret_code[RET_CODE_SIZE];
	char	*ptr_ret;

	ptr_ret = (char *)ret_code;
	ft_memset(ptr_ret, 0, RET_CODE_SIZE);
	putnbr_recursive(ms_data->return_code, &ptr_ret);
	*str = check_str(concat_str(*str, ret_code, (char *)ret_code + \
	ft_strlen((char *)ret_code)));
	start++;
	return (start);
}

// GET VARIABLE NAME
static char	*getvarname(char *start, char *end, char **var_name)
{
	char	*var_start;
	char	*var_end;

	var_start = start;
	while (start != end && ft_strchr(MS_VAR_CHAR, *start))
		start++;
	var_end = start;
	if (var_start < var_end)
		*var_name = check_str(substr(var_start, var_end));
	else
		*var_name = NULL;
	return (start);
}

// EXPAND VARIABLE
char	*expand_var(t_data *ms_data, char *start, char *end, char **str)
{
	char	*var_name;
	char	*var;

	start++;
	if (*start == '?')
		return (get_return_code(ms_data, start, str));
	var_name = NULL;
	start = getvarname(start, end, &var_name);
	if (!var_name)
	{
		if (ft_strchr(MS_QUOTES, *start))
			return (start);
		*str = check_str(concat_str(*str, start - 1, start));
		return (start);
	}
	var = getenv(var_name);
	free(var_name);
	if (var)
		*str = check_str(concat_str(*str, var, var + ft_strlen(var)));
	return (start);
}
