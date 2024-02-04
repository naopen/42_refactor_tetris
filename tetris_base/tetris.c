/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:16:01 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/04 20:16:02 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define R 20
#define C 15
#define T 1
#define F 0

char			Table[R][C] = {0};
int				final = 0;
char			GameOn = T;
suseconds_t		timer = 400000;
int				decrease = 1000;

typedef struct
{
	char		**array;
	int width, row, col;
}				Struct;
Struct			current;

const Struct	StructsArray[7] = {{(char *[]){(char[]){0, 1, 1}, (char[]){1, 1,
		0}, (char[]){0, 0, 0}}, 3}, {(char *[]){(char[]){1, 1, 0}, (char[]){0,
		1, 1}, (char[]){0, 0, 0}}, 3}, {(char *[]){(char[]){0, 1, 0},
		(char[]){1, 1, 1}, (char[]){0, 0, 0}}, 3}, {(char *[]){(char[]){0, 0,
		1}, (char[]){1, 1, 1}, (char[]){0, 0, 0}}, 3}, {(char *[]){(char[]){1,
		0, 0}, (char[]){1, 1, 1}, (char[]){0, 0, 0}}, 3},
		{(char *[]){(char[]){1, 1}, (char[]){1, 1}}, 2}, {(char *[]){(char[]){0,
		0, 0, 0}, (char[]){1, 1, 1, 1}, (char[]){0, 0, 0, 0}, (char[]){0, 0, 0,
		0}}, 4}};

Struct	CloneShape(Struct shape)
{
	Struct	new_shape;
	char	**copyshape;

	new_shape = shape;
	copyshape = shape.array;
	new_shape.array = (char **)malloc(new_shape.width * sizeof(char *));
	int i, j;
	for (i = 0; i < new_shape.width; i++)
	{
		new_shape.array[i] = (char *)malloc(new_shape.width * sizeof(char));
		for (j = 0; j < new_shape.width; j++)
		{
			new_shape.array[i][j] = copyshape[i][j];
		}
	}
	return (new_shape);
}

void	DestroyShape(Struct shape)
{
	int	i;

	for (i = 0; i < shape.width; i++)
	{
		free(shape.array[i]);
	}
	free(shape.array);
}

int	CanPlaceShape(Struct shape)
{
	char	**array;

	array = shape.array;
	int i, j;
	for (i = 0; i < shape.width; i++)
	{
		for (j = 0; j < shape.width; j++)
		{
			if ((shape.col + j < 0 || shape.col + j >= C || shape.row + i >= R))
			{
				if (array[i][j])
					return (F);
			}
			else if (Table[shape.row + i][shape.col + j] && array[i][j])
				return (F);
		}
	}
	return (T);
}

void	RotateShape(Struct shape)
{
	Struct	temp;

	temp = CloneShape(shape);
	int i, j, k, width;
	width = shape.width;
	for (i = 0; i < width; i++)
	{
		for (j = 0, k = width - 1; j < width; j++, k--)
		{
			shape.array[i][j] = temp.array[k][i];
		}
	}
	DestroyShape(temp);
}

void	PrintTetrisBoard(void)
{
	char	Buffer[R][C] = {0};

	int i, j;
	for (i = 0; i < current.width; i++)
	{
		for (j = 0; j < current.width; j++)
		{
			if (current.array[i][j])
				Buffer[current.row + i][current.col + j] = current.array[i][j];
		}
	}
	clear();
	for (i = 0; i < C - 9; i++)
		printw(" ");
	printw("42 Tetris\n");
	for (i = 0; i < R; i++)
	{
		for (j = 0; j < C; j++)
		{
			printw("%c ", (Table[i][j] + Buffer[i][j]) ? '#' : '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", final);
}

struct timeval before_now, now;
int	hasToUpdate(void)
{
	return (((suseconds_t)(now.tv_sec * 1000000 + now.tv_usec)
			- ((suseconds_t)before_now.tv_sec * 1000000
				+ before_now.tv_usec)) > timer);
}

void	set_timeout(int time)
{
	time = 1;
	timeout(1);
}

int	main(void)
{
	int		c;
	Struct	new_shape;
	Struct	temp;
	Struct	new_shape;
	Struct	temp;
	Struct	new_shape;

	srand(time(0));
	final = 0;
	initscr();
	gettimeofday(&before_now, NULL);
	set_timeout(1);
	new_shape = CloneShape(StructsArray[rand() % 7]);
	new_shape.col = rand() % (C - new_shape.width + 1);
	new_shape.row = 0;
	DestroyShape(current);
	current = new_shape;
	if (!CanPlaceShape(current))
	{
		GameOn = F;
	}
	PrintTetrisBoard();
	while (GameOn)
	{
		if ((c = getch()) != ERR)
		{
			temp = CloneShape(current);
			switch (c)
			{
			case 's':
				temp.row++; // move down
				if (CanPlaceShape(temp))
					current.row++;
				else
				{
					int i, j;
					for (i = 0; i < current.width; i++)
					{
						for (j = 0; j < current.width; j++)
						{
							if (current.array[i][j])
								Table[current.row + i][current.col
									+ j] = current.array[i][j];
						}
					}
					int n, m, sum, count = 0;
					for (n = 0; n < R; n++)
					{
						sum = 0;
						for (m = 0; m < C; m++)
						{
							sum += Table[n][m];
						}
						if (sum == C)
						{
							count++;
							int l, k;
							for (k = n; k >= 1; k--)
								for (l = 0; l < C; l++)
									Table[k][l] = Table[k - 1][l];
							for (l = 0; l < C; l++)
								Table[k][l] = 0;
							timer -= decrease--;
						}
					}
					final += 100 * count;
					new_shape = CloneShape(StructsArray[rand() % 7]);
					new_shape.col = rand() % (C - new_shape.width + 1);
					new_shape.row = 0;
					DestroyShape(current);
					current = new_shape;
					if (!CanPlaceShape(current))
					{
						GameOn = F;
					}
				}
				break ;
			case 'd':
				temp.col++;
				if (CanPlaceShape(temp))
					current.col++;
				break ;
			case 'a':
				temp.col--;
				if (CanPlaceShape(temp))
					current.col--;
				break ;
			case 'w':
				RotateShape(temp);
				if (CanPlaceShape(temp))
					RotateShape(current);
				break ;
			}
			DestroyShape(temp);
			PrintTetrisBoard();
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate())
		{
			temp = CloneShape(current);
			switch ('s')
			{
			case 's':
				temp.row++;
				if (CanPlaceShape(temp))
					current.row++;
				else
				{
					int i, j;
					for (i = 0; i < current.width; i++)
					{
						for (j = 0; j < current.width; j++)
						{
							if (current.array[i][j])
								Table[current.row + i][current.col
									+ j] = current.array[i][j];
						}
					}
					int n, m, sum, count = 0;
					for (n = 0; n < R; n++)
					{
						sum = 0;
						for (m = 0; m < C; m++)
						{
							sum += Table[n][m];
						}
						if (sum == C)
						{
							count++;
							int l, k;
							for (k = n; k >= 1; k--)
								for (l = 0; l < C; l++)
									Table[k][l] = Table[k - 1][l];
							for (l = 0; l < C; l++)
								Table[k][l] = 0;
							timer -= decrease--;
						}
					}
					new_shape = CloneShape(StructsArray[rand() % 7]);
					new_shape.col = rand() % (C - new_shape.width + 1);
					new_shape.row = 0;
					DestroyShape(current);
					current = new_shape;
					if (!CanPlaceShape(current))
					{
						GameOn = F;
					}
				}
				break ;
			case 'd':
				temp.col++;
				if (CanPlaceShape(temp))
					current.col++;
				break ;
			case 'a':
				temp.col--;
				if (CanPlaceShape(temp))
					current.col--;
				break ;
			case 'w':
				RotateShape(temp);
				if (CanPlaceShape(temp))
					RotateShape(current);
				break ;
			}
			DestroyShape(temp);
			PrintTetrisBoard();
			gettimeofday(&before_now, NULL);
		}
	}
	DestroyShape(current);
	endwin();
	int i, j;
	for (i = 0; i < R; i++)
	{
		for (j = 0; j < C; j++)
		{
			printf("%c ", Table[i][j] ? '#' : '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", final);
	return (0);
}
