/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:23:59 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/04 21:24:01 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define BOARD_ROWS 20
#define BOARD_COLS 15
#define TRUE 1
#define FALSE 0

char			Table[BOARD_ROWS][BOARD_COLS] = {0};
int				final = 0;
char			GameOn = TRUE;
suseconds_t		timer = 400000;
int				decrease = 1000;

typedef struct
{
	char		**array;
	int width, row, col;
}				Struct;
Struct			current;

const Struct StructsArray[7] = {
    {
        (char *[]){
            (char[]){0, 1, 1},
            (char[]){1, 1, 0},
            (char[]){0, 0, 0}
        },
        3
    },
    {
        (char *[]){
            (char[]){1, 1, 0},
            (char[]){0, 1, 1},
            (char[]){0, 0, 0}
        },
        3
    },
    {
        (char *[]){
            (char[]){0, 1, 0},
            (char[]){1, 1, 1},
            (char[]){0, 0, 0}
        },
        3
    },
    {
        (char *[]){
            (char[]){0, 0, 1},
            (char[]){1, 1, 1},
            (char[]){0, 0, 0}
        },
        3
    },
    {
        (char *[]){
            (char[]){1, 0, 0},
            (char[]){1, 1, 1},
            (char[]){0, 0, 0}
        },
        3
    },
    {
        (char *[]){
            (char[]){1, 1},
            (char[]){1, 1}
        },
        2
    },
    {
        (char *[]){
            (char[]){0, 0, 0, 0},
            (char[]){1, 1, 1, 1},
            (char[]){0, 0, 0, 0},
            (char[]){0, 0, 0, 0}
        },
        4
    }
};