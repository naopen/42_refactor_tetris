/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:29:18 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/04 20:39:45 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

typedef enum
{
	MOVE_LEFT,
	MOVE_RIGHT,
	ROTATE,
	SOFT_DROP,
	NO_INPUT
}				InputCommand;

InputCommand	ReadInput(void);

#endif // INPUT_H
