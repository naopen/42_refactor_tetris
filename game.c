/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:26:53 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/04 21:00:05 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "board.h"
#include "game.h"
#include "render.h"
#include "shapes.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ゲームの状態を管理するグローバル変数
static char		GameOn = true;
static int		finalScore = 0;
static Shape	currentShape;

// ゲームの初期化を行う関数
static void	InitializeGame(void)
{
	// ncursesの初期化
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE); // 特殊キーを有効にする
	// 乱数生成器の初期化
	srand(time(0));
	// ゲームボードの初期化
	ClearBoard();
	// 最初の形状を生成
	currentShape = CreateShape();
}

// ゲームの終了処理を行う関数
static void	FinalizeGame(void)
{
	// ncursesの終了処理
	endwin();
	// 最終スコアの表示
	printf("\nGame over!\n");
	printf("\nFinal Score: %d\n", finalScore);
}

// ゲームのメインループを行う関数
static void	GameLoop(void)
{
	InputCommand	command;

	while (GameOn)
	{
		// ユーザー入力を取得
		command = ReadInput();
		// 入力に応じて形状を操作
		ProcessInput(command, &currentShape);
		// ボードの状態を更新
		if (CanPlaceShape(currentShape))
		{
			UpdateBoard(currentShape);
		}
		else
		{
			// 形状がボードに固定されたときの処理
			HandleShapeLanding(&currentShape, &finalScore);
			currentShape = CreateShape(); // 新しい形状を生成
			if (!CanPlaceShape(currentShape))
			{
				GameOn = false; // 新しい形状がボードに配置できない場合はゲームオーバー
			}
		}
		// ボードと現在の形状を描画
		RenderBoard(GetBoard());
		RenderCurrentShape(currentShape);
		RenderScore(finalScore);
		// ループの遅延を管理
		DelayGameLoop();
	}
}

void	StartGame(void)
{
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, true); // trueに変更
	srand(time(NULL));
	ClearBoard();
	currentShape = CreateShape(); // CreateShape関数の定義が必要
	while (GameOn)
	{
		// ゲームループの内容
	}
	endwin();
	printf("\nGame over!\n");
	printf("\nFinal Score: %d\n", finalScore);
}
