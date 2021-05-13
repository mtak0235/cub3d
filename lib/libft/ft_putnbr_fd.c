/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:46:27 by mtak              #+#    #+#             */
/*   Updated: 2021/01/11 16:26:32 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	show_nbr(int n, int fd)
{
	if (n >= 10)
		show_nbr(n / 10, fd);
	write(fd, &"0123456789"[n % 10], 1);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	show_nbr(n, fd);
}
