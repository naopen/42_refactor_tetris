/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:28:23 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/04 20:43:58 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
#define SHAPES_H

#define SHAPE_ARRAY_SIZE 4

typedef struct {
    int array[SHAPE_ARRAY_SIZE][SHAPE_ARRAY_SIZE];
    int width, row, col; // widthは形状の幅、rowとcolは形状の現在の位置
} Shape;

void InitializeShape(Shape *shape, int type);
void RotateShape(Shape *shape);
void MoveShape(Shape *shape, int direction);

#endif // SHAPES_H
