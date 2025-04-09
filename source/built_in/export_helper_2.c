/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikelitoris <mikelitoris@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:42:51 by mikelitoris       #+#    #+#             */
/*   Updated: 2024/12/05 16:46:05 by mikelitoris      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	case_no_equal(char **argv, t_data *ms_data, int i)
{
	(void)argv;
	if (is_variable_name_ok(argv[i]) == 0)
		prepare_error("not a valid identifier", argv[i], ms_data, 1);
}
