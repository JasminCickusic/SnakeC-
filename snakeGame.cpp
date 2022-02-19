

#include <iostream>
#include <conio.h>   // za input funkciju
#include <windows.h>  // za sleep funkciju

using namespace std;
bool gameOver;
const int width = 20;   // sirina i duzina mape
const int height = 20;
int x, y, fruitX, fruitY, score;  // potrebne varijable
int tailX[100], tailY[100];
int nTail;


enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};  //Za kretanje po mapi
eDirection dir;  // za drzanje kretanja zmije


void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}
void Draw()
{
    system("cls");

    for (int i = 0; i < width+2; i++)  // za kreiranje rubova mape po X osi
        cout << "#";
        cout << endl;



        for (int i = 0; i < height; i++)  //za printanje mape
        {
            for (int j = 0; j < width; j++)
            {
                if (j == 0)      // za pocetni dio mape po y osi
                    cout << "#";
                
                if (i == y && j == x)   // za kreiranje GlaveZmije
                    cout << "O";
                else if (i == fruitY && j == fruitX)   // za kreiranje HraneZaZmiju
                    cout << "F";
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++)     // za printanje repa/taila
                    {
                        
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << "o";
                            print = true;
                        }
                      
                    } 
                    if (!print)
                        cout << " ";
                }
                   

                if (j == width - 1)  // za desni dio mape  po y osi
                    cout << "#";
            }
            cout << endl;
        }



        for (int i = 0; i < width+2; i++)   // za kreiranje rubova po < osi  +1 zbog zadnjeg # da ga ispisse
            cout << "#";
        cout << endl;

        cout << "Score:" << score << endl;

}
void Input()
{
    if (_kbhit())   // da li je dugme pritisnuto "is keyboard pressed"
    {
        switch (_getch())
        {                       // za kretanje po mapi
        case 'a':
            dir = LEFT;
            break;
        
        case 'd':
            dir = RIGHT;
            break;

        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;

        case 'x':
            gameOver = true;
            break;
        }
    }
}
void Logic()    // logika kretanja
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y; 
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;

    case RIGHT:
        x++;
        break;

     case UP:
         y--;
        break;
     

        case DOWN:
            y++;
            break;

        
        default:
            break;
    }
   // if (x > width || x < 0 || y > height || y < 0 )    // ako udari u ivicu gameOver
      //  gameOver = true;

    if (x >= width) x = 0;  else if (x < 0) x = width - 1;    // kad proðe na desni zid izaðe na lijevoj strani i obratno
    if (y >= height) y = 0;  else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)    // za tail da se igra zavrsi ako sami sebe udarimo
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}
int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(10);
    }
    return 0;
}

