/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:28:53 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/04 20:44:31 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include <string.h>

// 形状のテンプレートを定義
const int SHAPES_TEMPLATES[7][SHAPE_ARRAY_SIZE][SHAPE_ARRAY_SIZE] = {
    // 各形状（I, O, T, S, Z, J, L）のテンプレート
    // ここでは、例として「I」形状だけを示す
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // 他の形状のテンプレートも同様に定義...
};

// 指定されたタイプの形状を初期化
void InitializeShape(Shape *shape, int type) {
    // typeに基づいてテンプレートから形状データをコピー
    memcpy(shape->array, SHAPES_TEMPLATES[type], sizeof(shape->array));
    shape->width = SHAPE_ARRAY_SIZE;
    shape->row = 0;
    shape->col = 0;
}

// 形状を時計回りに90度回転
void RotateShape(Shape *shape) {
    int tmp[SHAPE_ARRAY_SIZE][SHAPE_ARRAY_SIZE];
    int i, j;
    // 一時配列に転置をコピー
    for (i = 0; i < shape->width; ++i) {
        for (j = 0; j < shape->width; ++j) {
            tmp[j][shape->width - i - 1] = shape->array[i][j];
        }
    }
    // 元の配列に回転したデータをコピー
    memcpy(shape->array, tmp, sizeof(tmp));
}

// 形状を指定された方向に移動（左: -1, 右: 1, 下: 0）
void MoveShape(Shape *shape, int direction) {
    // directionに基づいて形状の位置を更新
    if (direction == -1) { // 左に移動
        shape->col -= 1;
    } else if (direction == 1) { // 右に移動
        shape->col += 1;
    } else { // 下に移動
        shape->row += 1;
    }
}
