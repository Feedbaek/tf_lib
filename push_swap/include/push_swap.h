/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 21:42:31 by minskim2          #+#    #+#             */
/*   Updated: 2021/08/24 18:50:46 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <unistd.h>
#include <stdlib.h>

typedef struct s_inform
{
	int	*stack_a;
	int	*stack_b;
	int	size_a;
	int	size_b;
}	t_inform;

void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif
