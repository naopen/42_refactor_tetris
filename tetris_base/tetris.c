/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:16:01 by nkannan           #+#    #+#             */
/*   Updated: 2024/02/04 21:24:39 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"


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
			if ((shape.col + j < 0 || shape.col + j >= BOARD_COLS || shape.row + i >= BOARD_ROWS))
			{
				if (array[i][j])
					return (FALSE);
			}
			else if (Table[shape.row + i][shape.col + j] && array[i][j])
				return (FALSE);
		}
	}
	return (TRUE);
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
	char	Buffer[BOARD_ROWS][BOARD_COLS] = {0};

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
	for (i = 0; i < BOARD_COLS - 9; i++)
		printw(" ");
	printw("42 Tetris\n");
	for (i = 0; i < BOARD_ROWS; i++)
	{
		for (j = 0; j < BOARD_COLS; j++)
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

	srand(time(0));
	final = 0;
	initscr();
	gettimeofday(&before_now, NULL);
	set_timeout(1);
	new_shape = CloneShape(StructsArray[rand() % 7]);
	new_shape.col = rand() % (BOARD_COLS - new_shape.width + 1);
	new_shape.row = 0;
	DestroyShape(current);
	current = new_shape;
	if (!CanPlaceShape(current))
	{
		GameOn = FALSE;
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
					for (n = 0; n < BOARD_ROWS; n++)
					{
						sum = 0;
						for (m = 0; m < BOARD_COLS; m++)
						{
							sum += Table[n][m];
						}
						if (sum == BOARD_COLS)
						{
							count++;
							int l, k;
							for (k = n; k >= 1; k--)
								for (l = 0; l < BOARD_COLS; l++)
									Table[k][l] = Table[k - 1][l];
							for (l = 0; l < BOARD_COLS; l++)
								Table[k][l] = 0;
							timer -= decrease--;
						}
					}
					final += 100 * count;
					new_shape = CloneShape(StructsArray[rand() % 7]);
					new_shape.col = rand() % (BOARD_COLS - new_shape.width + 1);
					new_shape.row = 0;
					DestroyShape(current);
					current = new_shape;
					if (!CanPlaceShape(current))
					{
						GameOn = FALSE;
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
					for (n = 0; n < BOARD_ROWS; n++)
					{
						sum = 0;
						for (m = 0; m < BOARD_COLS; m++)
						{
							sum += Table[n][m];
						}
						if (sum == BOARD_COLS)
						{
							count++;
							int l, k;
							for (k = n; k >= 1; k--)
								for (l = 0; l < BOARD_COLS; l++)
									Table[k][l] = Table[k - 1][l];
							for (l = 0; l < BOARD_COLS; l++)
								Table[k][l] = 0;
							timer -= decrease--;
						}
					}
					new_shape = CloneShape(StructsArray[rand() % 7]);
					new_shape.col = rand() % (BOARD_COLS - new_shape.width + 1);
					new_shape.row = 0;
					DestroyShape(current);
					current = new_shape;
					if (!CanPlaceShape(current))
					{
						GameOn = FALSE;
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
	for (i = 0; i < BOARD_ROWS; i++)
	{
		for (j = 0; j < BOARD_COLS; j++)
		{
			printf("%c ", Table[i][j] ? '#' : '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", final);
	return (0);
}
