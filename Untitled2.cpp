#include <iostream>
#include <bits/stdc++.h>
#include <cmath>
#include <ctime>
#include <conio.h>

using namespace std;

#define KEY_UP 72 //defining up key as 72
#define KEY_DOWN 80 //specific value returned by OS for specific keys
#define KEY_LEFT 75
#define KEY_RIGHT 77

const int WINNER = 2048;

void left(int array[4][4], int & score)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			if (array[i][j] > 0)
			{
				if (array[i][j-1] == 0)
				{	
					while (array[i][j-1] == 0)
					{
						array[i][j-1] = array[i][j];
						array[i][j] = 0;
						j--;
						
						if (j == 0)
						break;
					}
				}
				if (array[i][j-1] == array[i][j])
				{
					array[i][j-1] = array[i][j-1]*2;
					score = score + array[i][j-1]*2;
					array[i][j] = 0;
				}
			}
		}
	}
}

void right(int array[4][4], int & score)
{
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 2; j >=  0; j--)
		{
			if (array[i][j] > 0)
			{
				if (array[i][j+1] == 0)
				{	
					while (array[i][j+1] == 0)
					{
						array[i][j+1] = array[i][j];
						array[i][j] = 0;
						j++;
						
						if (j == 3)
						break;
					}
				}
				if (array[i][j+1] == array[i][j])
				{
					array[i][j+1] = array[i][j+1]*2;
					score = score + array[i][j+1]*2;
					array[i][j] = 0;
				}
			}
		}
	}
}

void up(int array[4][4], int & score)
{
	for (int i = 1; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (array[i][j] > 0)
			{
				if (array[i-1][j] == 0)
				{	
					while (array[i-1][j] == 0)
					{
						array[i-1][j] = array[i][j];
						array[i][j] = 0;
						i--;
						
						if (i == 0)
						break;
					}
				}
				if (array[i-1][j] == array[i][j])
				{
					array[i-1][j] = array[i-1][j]*2;
					score = score + array[i-1][j]*2;
					array[i][j] = 0;
				}
			}
		}
	}
}

void down(int array[4][4], int & score)
{
	for (int i = 2; i >= 0; i--)
	{
		for (int j = 3; j >=  0; j--)
		{
			if (array[i][j] > 0)
			{
				if (array[i+1][j] == 0)
				{	
					while (array[i+1][j] == 0)
					{
						array[i+1][j] = array[i][j];
						array[i][j] = 0;
						i++;
						
						if (i == 3)
						break;
					}
				}
				if (array[i+1][j] == array[i][j])
				{
					array[i+1][j] = array[i+1][j]*2;
					score = score + array[i+1][j]*2;
					array[i][j] = 0;
				}
			}
		}
	}
}

void tiles (int array[4][4])
{
  srand(time(0));
  int insert;
  bool condition = true;

    while (condition == true)
    {
      if ((rand() % 10) + 1 == 4)
        insert = 4;
      else 
        insert = 2;
  
      int row = (rand() % 3);
      int column = (rand() % 3);
  
      if (array[row][column] == 0)
      {
        array[row][column] = insert;
        condition = false;
        }
      }
  }

void output(int array[4][4])
{
  cout<<"--------------------"<<endl;
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      {
        cout<<"| "<<array[i][j]<<" |";
      }      
      cout<<endl;
	  if (i == 3)
	    cout<<"--------------------"<<endl;
	}
}

void readDirection(int array[4][4], int & score)
{
	int c = 0;
	bool condition = false;
    while(condition == false) //change condition
    {
        c = 0;

        switch((c=getch())) //getch returns ASCII value of character
		{
        case KEY_UP:
            up(array, score);
            condition = true;
            break;
        case KEY_DOWN:
            down(array, score);
            condition = true;
            break;
        case KEY_LEFT:
            left(array, score);
            condition = true;
            break;
        case KEY_RIGHT:       
            right(array, score);
            condition = true;
            break;        
        }

    }
}

bool checkWin(int array[4][4])
{
  for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
        {
          if (array[i][j] == WINNER)
            return true;
        }
    }
  return false;
}

int checkLoss(int array[4][4])
{
	int counter = 0;
	for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
        {
          if (array[i][j] > 0)
            counter++;
        }
    }
    return counter;
}

int main()
{
  int game[4][4] = {};
  string answer;
  int numbMoves = 1;
  int score = 0;
  
  cout<<"Are you ready to begin?: ";
  cin >> answer;

  if (answer == "yes" || answer == "Yes")
   cout<<"Let's Begin!"<<endl;
  else 
    return 0;
  
  tiles(game);
  tiles(game); // Two tiles to start game
  output(game);
  
  int c = _getch();
  while(c != 27) //Uses escape to stop game
  {
  		
	readDirection(game, score);	
	tiles(game);
	system("CLS");
	output(game);
	cout<<"Number of moves: "<<numbMoves<<endl;
	cout<<"Your Score: "<<score/2<<endl;
	numbMoves++;
	  
    c = _getch();
    
  	if (checkWin(game))
  	{
  		cout<<"CONGRATULATIONS YOU WIN!"<<endl;
  		return 0;
	}
	if (checkLoss(game) == 16)
	{
		cout<<"CONGRATULATIONS YOU LOSE!"<<endl;
		return 0;
	}
  }

  return 0;
}
