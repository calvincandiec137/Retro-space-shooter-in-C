#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>

typedef struct
{
	int x, y;
	int active;
}Bullet, Enemy;

#define maxb 20
#define maxene 2

Bullet bullets[maxb];
int baccess = 0;

Enemy enemy[maxene];

int spaceshipX = 300;
int spaceshipY = 400;
int score = 0;


void drawspaceship(int x, int y) ;
void handle();
void game();
void initbullet();
int updateWorld();
void moveenemy();
void enemy_ghost(int x,int y);
void movebullet();
void updateScore();
void drawenemy();
void drawbullet();
void bullet_circle(int x, int y);
int detect();
void celebrate();
void death();

void main()
{
	int gd = DETECT, gm, c;
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

	initbullet();

	while (1) 
  {

		cleardevice();
		printf("MENU:-\n1. Play\n2. Exit\nLast score: %d\n\nYour selection:", score);
		scanf("%d", &c);

		switch (c) 
    {
			case 1: 
      {
				game();
				break;
			}
			case 2: 
      {
				closegraph();
				break;
			}
			default: 
      {
				printf("Invalid choice. Please choose again.\n");
				break;
			}
		}
	}
}


void initbullet()
{
	int i;
	for (i = 0; i < maxb; i++)
	{
		bullets[i].active = 0;
	}

	for (i = 0; i < maxene; i++)
	{
		enemy[i].active = 0;
	}
}

void game()
{
	int gameOver;
	while (1)
	{
		cleardevice();
		handle();
		gameOver = updateWorld();
		delay(30);

		if (gameOver == 1)
		{
			break;
		}
	}
}

void handle()
{
	if (kbhit())
	{
		char ch = getch();

		if (ch == 0)
		{
			ch = getch();

			switch (ch)
			{
				case 0x4B:  //Left arrow
					spaceshipX -= 20;
					if (spaceshipX < 10) spaceshipX = 10;
					break;
				case 0x4D: //Right arrow
					spaceshipX += 20;
					if (spaceshipX > getmaxx() - 10)
					{
						spaceshipX = getmaxx() - 10;
					}
					break;
				case 0x48: //top arrow button
					bullets[baccess].x = spaceshipX;
					bullets[baccess].y = spaceshipY - 20;
					bullets[baccess++].active = 1;
					baccess = (baccess + 1) % 20;
					break;
			}
		}
	}
}

int updateWorld()
{
	int flag;
	movebullet();
	moveenemy();
	drawspaceship(spaceshipX, spaceshipY);
	updateScore();
	drawenemy();
	drawbullet();
	flag = detect();
	if (flag == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void movebullet()
{
	int i;
	for (i = 0; i < maxb; i++)
	{
		if (bullets[i].y < 0)
		{
			bullets[i].active = 0;
			continue;
		}
		bullets[i].y -= 4;
	}
}

void moveenemy()
{
	int i, j;
	for (i = 0; i < maxene; i++)
	{
		if (enemy[i].active == 1)
		{
			enemy[i].y += 2;
		}

	}

	//enemy generation code
	for (i = 0; i < maxene - 1; i++)
	{
		if (enemy[i].active == 0 )
		{
			enemy[i].active = 1;
			enemy[i].y = 0;
			enemy[i].x = 30 + (rand() % (getmaxx() - 60));
			break;
		}
	}
}

int detect()
{
	int i, j;

	//Check if any of the bullet hits any of the enemies
	for (i = 0; i < maxb; i++)
	{
		if (bullets[i].active == 1)
		{
			for (j = 0; j < maxene; j++)
			{
				if (bullets[i].x <= (enemy[j].x + 30) && bullets[i].x >= (enemy[j].x) && bullets[i].y <= (enemy[j].y + 40))
				{
					enemy[j].active = 0;
					bullets[i].active = 0;
					score++;
				}
			}
		}
	}

	//check if the enemy has reached the area behind the spaceship
	for (j = 0; j < maxene; j++)
	{
		if (enemy[j].active == 1 && enemy[j].y > getmaxy())
		{
			death();
			delay(5000);
			return 1;
		}
	}

	//check score
	if (score >= 9)
	{
		celebrate();
		delay(5000);
		return 1;
	}

	return 0;
}

void celebrate()
{
	char *text = " VICTORYYY!!!!!";
	cleardevice();
	settextstyle(DEFAULT_FONT,HORIZ_DIR, 5);
	setcolor(YELLOW);
	outtextxy(10, 200, text);
}

void death()
{
	char *text = "You Died :(";
	cleardevice();
	settextstyle(DEFAULT_FONT,HORIZ_DIR, 5);
	setcolor(RED);
	outtextxy(10, 200, text);
}

void drawspaceship(int x, int y)
{       
  setcolor(WHITE);
	line(x, y - 2, x - 2, y - 2);
	line(x - 2, y - 2, x - 2, y - 10);
	line(x - 2, y - 10, x - 5, y - 10);
	line(x - 5, y - 10, x - 5, y - 7);
	line(x - 5, y - 7, x - 7, y - 7);
	line(x - 7, y - 7, x - 7, y - 5);
	line(x - 7, y - 5, x - 10, y - 5);
	line(x - 10, y - 5, x - 10, y - 2);
	line(x - 10, y - 2, x - 12, y - 2);
	line(x - 12, y - 2, x - 12, y);
	line(x - 12, y, x - 15, y);
	line(x - 15, y, x - 15, y - 15);
	line(x - 15, y - 15, x - 12, y - 15);
	line(x - 12, y - 15, x - 12, y - 5);
	line(x - 12, y - 5, x - 10, y - 5);
	line(x - 10, y - 5, x - 10, y - 10);
	line(x - 10, y - 10, x - 7, y - 10);
	line(x - 7, y - 10, x - 7, y - 15);
	line(x - 7, y - 15, x - 2, y - 15);
	line(x - 2, y - 15, x - 2, y - 27);
	line(x - 2, y - 27, x - 1, y - 27);
	line(x - 1, y - 27, x - 1, y - 35);
	line(x - 1, y - 35, x, y - 35);

	line(x, y - 2, x + 2, y - 2);
	line(x + 2, y - 2, x + 2, y - 10);
	line(x + 2, y - 10, x + 5, y - 10);
	line(x + 5, y - 10, x + 5, y - 7);
	line(x + 5, y - 7, x + 7, y - 7);
	line(x + 7, y - 7, x + 7, y - 5);
	line(x + 7, y - 5, x + 10, y - 5);
	line(x + 10, y - 5, x + 10, y - 2);
	line(x + 10, y - 2, x + 12, y - 2);
	line(x + 12, y - 2, x + 12, y);
	line(x + 12, y, x + 15, y);
	line(x + 15, y, x + 15, y - 15);
	line(x + 15, y - 15, x + 12, y - 15);
	line(x + 12, y - 15, x + 12, y - 5);
	line(x + 12, y - 5, x + 10, y - 5);
	line(x + 10, y - 5, x + 10, y - 10);
	line(x + 10, y - 10, x + 7, y - 10);
	line(x + 7, y - 10, x + 7, y - 15);
	line(x + 7, y - 15, x + 2, y - 15);
	line(x + 2, y - 15, x + 2, y - 27);
	line(x + 2, y - 27, x + 1, y - 27);
	line(x + 1, y - 27, x + 1, y - 35);
	line(x + 1, y - 35, x, y - 35);
	setfillstyle(SOLID_FILL,RED);
	floodfill(x+1, y-15,WHITE);
}

void updateScore()
{
	char text[20] = "Score: ";
	sprintf(text + 6, "%d", score);
	settextstyle(DEFAULT_FONT,HORIZ_DIR, 2);
	setcolor(WHITE);
	outtextxy((getmaxx() - 120), 10, text);
}

void drawenemy()
{
	int i;

	for (i = 0; i < maxene; i++)
	{
		if (enemy[i].active == 1)
		{
			setcolor(WHITE);
			enemy_ghost(enemy[i].x, enemy[i].y);
		}
	}
}

void enemy_ghost(int x,int y)
{

    setcolor(WHITE);


    rectangle(x, y, x + 30, y + 30);


    rectangle(x + 8, y + 8, x + 13, y + 13);
    rectangle(x + 20, y + 8, x + 25, y + 15);


    rectangle(x + 4, y + 26, x + 8, y + 30);
    rectangle(x + 12, y + 26, x + 16, y + 30);
    rectangle(x + 20, y + 26, x + 24, y + 30);
    setfillstyle(SOLID_FILL,BLUE);
    floodfill(x+6,y+20,WHITE);

}

void drawbullet()
{
	int i;
	for (i = 0; i < maxb; i++)
	{
		if (bullets[i].active == 1)
		{
			setcolor(WHITE);
			bullet_circle(bullets[i].x, bullets[i].y);
		}
	}
}

void bullet_circle(int x, int y)
{
    setcolor(RED);            
    circle(x, y, 3);        
    setfillstyle(SOLID_FILL, YELLOW);  
    floodfill(x, y, RED);     
}
