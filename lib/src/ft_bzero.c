/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:58:01 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/07/12 14:35:11 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	ft_bzero(void *s, size_t n)
{
	char *ps;

	ps = s;
	while (n > 0)
	{
		*ps = 0;
		ps++;
		n--;
	}
}