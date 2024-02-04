/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:30:10 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/04 21:19:51 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define C 10

void	RenderBoard(const char board[][BOARD_COLS]);
void	RenderScore(const int score);

#endif // RENDER_H
