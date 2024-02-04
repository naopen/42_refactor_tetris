/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:29:52 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/04 20:40:37 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include <ncurses.h>

InputCommand	ReadInput(void)
{
	int	ch;

	ch = getch();
	if (ch == KEY_LEFT || ch == 'a')
	{
		return (MOVE_LEFT);
	}
	else if (ch == KEY_RIGHT || ch == 'd')
	{
		return (MOVE_RIGHT);
	}
	else if (ch == KEY_UP || ch == 'w')
	{
		return (ROTATE);
	}
	else if (ch == KEY_DOWN || ch == 's')
	{
		return (SOFT_DROP);
	}
	else
	{
		return (NO_INPUT);
	}
}
