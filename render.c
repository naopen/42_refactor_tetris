/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:30:30 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/04 21:19:51 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <ncurses.h>

// ゲームボードの描画
void RenderBoard(const char board[][BOARD_COLS]) {
    // ncursesを使用してゲームボードを描画
    int row = 0;
    int col;
    while (row < R) {
        col = 0;
        move(row, 0); // ncursesのカーソル移動関数
        while (col < BOARD_COLS) {
            // ボードのブロックが存在する場合は'#'を、そうでなければ'.'を表示
            char display_char = board[row][col] ? '#' : '.';
            addch(display_char);
            addch(' '); // スペースを追加して見やすくする
            ++col;
        }
        ++row;
    }
    refresh(); // 描画を画面に反映
}

// スコアの描画
void RenderScore(const int score) {
    move(R, 0); // スコアを表示する行にカーソルを移動
    printw("Score: %d", score);
    refresh(); // 描画を画面に反映
}
