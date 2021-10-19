/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 00:52:21 by minskim2          #+#    #+#             */
/*   Updated: 2021/10/19 20:50:32 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_atoi(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (*str == '\t' || *str == ' '
		|| *str == '\n' || *str == '\f'
		|| *str == '\v' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		i *= 10;
		i += *str - '0';
		str++;
	}
	if (*str)
		return (0);
	return (sign * i);
}

void	print_msg(t_philo *philo, int status)
{
	struct timeval	current_time;
	size_t			time;

	if (philo->status == DIE)
		return ;
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec - philo->start_time.tv_sec) \
		* 1000 + ((current_time.tv_usec - philo->start_time.tv_usec) / 1000);
	if (status == DIE)
		printf("%ld %d is died\n", time, philo->num);
	else if (status == THINK)
		printf("%ld %d is thinking\n", time, philo->num);
	else if (status == FORK)
		printf("%ld %d has taken a fork\n", time, philo->num);
	else if (status == EAT)
		printf("%ld %d is eating\n", time, philo->num);
	else if (status == SLEEP)
		printf("%ld %d is sleeping\n", time, philo->num);
}
