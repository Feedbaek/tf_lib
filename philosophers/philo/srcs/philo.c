/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 19:20:08 by minskim2          #+#    #+#             */
/*   Updated: 2021/10/06 19:59:54 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

//void	print_status(t_philo *philo)
//{
//	if (philo->status == THINK)
//		printf("%ld %d is thinking\n", (philo->age), philo->num);
//	else if (philo->status == FORK)
//		printf("%ld %d has taken a fork\n", (philo->age), philo->num);
//	else if (philo->status == EAT)
//		printf("%ld %d is eating\n", (philo->age), philo->num);
//	else if (philo->status == SLEEP)
//		printf("%ld %d is sleeping\n", (philo->age), philo->num);
//	else if (philo->status == DIE)
//		printf("%ld %d died\n", (philo->age), philo->num);
//}

void	*running_pthread(void *p)
{
	t_philo			*philo;
	int				idx;
	struct timeval	start;
	struct timeval	end;

	philo = (t_philo *)p;
	idx = philo->num - 1;
	gettimeofday(&start, NULL);
	gettimeofday(&philo->time_to_die, NULL);
	while (philo->num_eat < philo->time_opt)
	{
		// 생각 시간
		philo->status = THINK;
		philo->change = 1;
		gettimeofday(&end, NULL);
		//philo->age = (end.tv_sec - start.tv_sec) * 1000 + ((end.tv_usec - start.tv_usec) / 1000);
		//print_status(philo);
		// if 왼쪽 포크가 있으면,
		// pthread_muxtex_lock(왼쪽 포크);
		if (idx)
		{
			pthread_mutex_lock(&philo->mutex[idx]);
			philo->status = FORK;
			philo->change = 1;
			gettimeofday(&end, NULL);
			//philo->age = (end.tv_sec - start.tv_sec) * 1000 + ((end.tv_usec - start.tv_usec) / 1000);
			//print_status(philo);
		// if 오른쪽 포크가 있으면,
		// pthread_muxtex_lock(오른쪽 포크);
			pthread_mutex_lock(&philo->mutex[(idx + 1) % philo->philo_num]);
		}
		else // 첫 철학자는 오른쪽 포크부터 확인함.
		{
			pthread_mutex_lock(&philo->mutex[(idx + 1) % philo->philo_num]);
			philo->status = FORK;
			philo->change = 1;
			gettimeofday(&end, NULL);
			//philo->age = (end.tv_sec - start.tv_sec) * 1000 + ((end.tv_usec - start.tv_usec) / 1000);
			//print_status(philo);
			pthread_mutex_lock(&philo->mutex[idx]);
		}
		// 식사 타임
		philo->status = EAT;
		philo->change = 1;
		gettimeofday(&end, NULL);
		gettimeofday(&philo->time_to_die, NULL);
		//philo->age = (end.tv_sec - start.tv_sec) * 1000 + ((end.tv_usec - start.tv_usec) / 1000);
		//print_status(philo);
		usleep(philo->time_eat * 1000);
		pthread_mutex_unlock(&philo->mutex[idx]);
		pthread_mutex_unlock(&philo->mutex[(idx + 1) % philo->philo_num]);
		philo->num_eat += 1;
		// pthread_mutex_unlock(왼쪽 포크);
		// pthread_mutex_unlock(오른쪽 포크);

		// 식사 끝나면자는 시간
		philo->status = SLEEP;
		philo->change = 1;
		gettimeofday(&end, NULL);
		//philo->age = (end.tv_sec - start.tv_sec) * 1000 + ((end.tv_usec - start.tv_usec) / 1000);
		//print_status(philo);
		usleep(philo->time_sleep * 1000);
	}
	return (p);
}

void	print_msg(t_philo *philo)
{
	if (philo->status == THINK)
		printf("%ld %d is thinking\n", philo->age, philo->num);
	else if (philo->status == FORK)
		printf("%ld %d has taken a fork\n", philo->age, philo->num);
	else if (philo->status == EAT)
		printf("%ld %d is eating\n", philo->age, philo->num);
	else if (philo->status == SLEEP)
		printf("%ld %d is sleeping\n", philo->age, philo->num);
}

void	*mornitor_pthread(void *s)
{
	int				i;
	t_simul			*simul;
	struct timeval	start_time;
	struct timeval	*last_eat;
	struct timeval	current_time;

	simul = (t_simul *)s;
	last_eat = (struct timeval *)malloc(sizeof(struct timeval) * simul->philo_num);
	if (!last_eat)
		return (0);
	gettimeofday(&start_time, NULL);
	i = 0;
	while (i < simul->philo_num)
	{
		gettimeofday(&last_eat[i], NULL);
		i++;
	}
	while (1)
	{
		i = 0;
		while (i < simul->philo_num)
		{
			// 죽었는지 검사, 아무도 안죽었으면 상태 변화 감지 단계로 넘어감.
			gettimeofday(&current_time, NULL);
			simul->philo[i].age = (current_time.tv_sec - start_time.tv_sec) * 1000 + ((current_time.tv_usec - start_time.tv_usec) / 1000);
			//printf("check_die: %ld ", simul->philo[i].age);
			if ((current_time.tv_sec - last_eat[i].tv_sec) * 1000 + ((current_time.tv_usec - last_eat[i].tv_usec) / 1000) >= simul->time_die)
			{
				printf("%ld %d died\n", simul->philo[i].age, simul->philo[i].num);
				return (s);
			}
			i++;
			//gettimeofday(&check_time, NULL);
			//if ((check.tv_sec - simul->philo[i].time_to_die.tv_sec) * 1000 + ((check.tv_usec - simul->philo[i].time_to_die.tv_usec) / 1000) >= simul->time_die)
			//{
			//	printf("========= death %d : %ld ==========\n", i + 1, (check.tv_sec - simul->philo[i].time_to_die.tv_sec) * 1000 + ((check.tv_usec - simul->philo[i].time_to_die.tv_usec) / 1000));
			//	return (0);
			//}
		}
		i = 0;
		while (i < simul->philo_num) // 죽은 철학자가 없으니 변화가 있는지 검사
		{
			gettimeofday(&current_time, NULL);
			simul->philo[i].age = (current_time.tv_sec - start_time.tv_sec) * 1000 + ((current_time.tv_usec - start_time.tv_usec) / 1000);
			//printf("check_change: %ld ", simul->philo[i].age);
			if (simul->philo[i].change)
			{
				if (simul->philo[i].status == EAT)
				{
					gettimeofday(&last_eat[i], NULL);
				}
				print_msg(&simul->philo[i]);
				simul->philo[i].change = 0;
			}
			i++;
		}
	}
	return (s);
}

int	wait_pthread(t_simul *simul)
{
	int	i;
	int	status;
	int	*ret;

	i = 0;
	status = pthread_create(&simul->thread[simul->philo_num], NULL, mornitor_pthread, (void *)simul);
	if (status < 0)
		return (0);
	pthread_join(simul->thread[simul->philo_num], (void *)&ret);
	if (ret == 0)
		return (0);
	//while(i < simul->philo_num)
	//{
	//	pthread_join(simul->thread[i], NULL);
	//	pthread_mutex_unlock(&simul->mutex[i]);
	//	pthread_mutex_destroy(&simul->mutex[i]);
	//	i++;
	//}
	return (1);
}

int	main(int argc, char **argv)
{
	t_simul	simul;

	if (!init_simul(&simul, argc, argv) || !init_pthread_mutex(&simul))
		return (-1);
	if (!wait_pthread(&simul))
		return (-1);
	// mutex_destroy 필요
	return (0);
}
