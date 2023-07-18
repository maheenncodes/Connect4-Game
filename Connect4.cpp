#include<string>
#include<iostream>

using namespace std;


struct connect4{

    connect4(string Names[]){
        re_init(Names);
    }
    connect4(){
        string N[2] = {"P1", "P2"};
        re_init(N);
    }
    void re_init(string Names[]){
        for(int i = 0; i< 7; i++){
            ColumnMoves[i]= 5;
            for(int j = 0; j< 6; j++)
                Data[j][i] = 32; // 32 is code of space character
        }
        Result = 0;
        GameOver = 0;
        PlayerNames[0] = Names[1];
        PlayerNames[1] = Names[0];
        PlayerChar[0] = 'o';
        PlayerChar[1] = 'x';
        PlayerWinningChar[0] = 'O';
        PlayerWinningChar[1] = 'X';
    }

    int MakeMove(int Column){
    /*
        This Function must make a move in the Column given as a parameter
        The function will use the function GameOver() to mark is the game
        is completed and set the value of variables GameOver and Result.
        The function must also update the array ColumnMoves.

        The function must return 0 if the move has been made, 1 if the move
        is invalid (can not be done as the column is already filled) and 2
        if the game is already over.

        This function must also change the value of TurningPlayer if the move
        was successful;
    */
    int rows = ColumnMoves[Column - 1];
    int PlayersTurn;
    PlayersTurn = WhosTurn();

    if(PlayersTurn == 0)
    {
        Data[rows][Column - 1] = PlayerChar[0];
    }
    else
    {
        Data[rows][Column - 1] = PlayerChar[1];
    }
    ColumnMoves[Column-1] = rows - 1;

    if(CheckIfGameOver(rows,Column-1))
    {
        return 0;
    }

    return 1;

}


   void ShowGame(){
    /*
        Function to display the game status on screen;
    */
      cout << endl;
      cout<<"  1   2   3   4   5   6   7 "<<endl;

      for (int i= 0; i<6; i++)
      {
         for (int j = 0; j<7;j++)
         {
            cout <<"| ";
            cout << Data[i][j];
            cout <<" ";
         }
         cout<<"| ";
         cout << endl;
         cout <<"----------------------------------"<<endl;
      }


}

   int isGameOver(){


        return GameOver;



    }

    int WhosTurn(){
        TurningPlayer++;
        if(TurningPlayer%2==0)
    	{
    		TurningPlayer=0;
		}
		else
		{
			TurningPlayer=1;
		}
        return TurningPlayer;
    }

    string getPlayerName(int id){
        if(id< 0 || id > 1 )
            return "";
        return PlayerNames[id];
    }

private :

    bool CheckIfGameOver(int r, int c) {
    /*
        This function will check if the game is finished and set the values
        of variables GameOver and Result
        The parameters r and c specify the position of the last move.
    */
    if (Data[r][c] != char(32)) {
        char Turningplayer = Data[r][c];
        char winchar = (Turningplayer == 'o') ? 'O' : 'X';

        // Vertical check
        int vertical = 1;
        for (int vertcheck = r + 1; vertcheck <= 5 && Data[vertcheck][c] == Turningplayer; vertcheck++, vertical++);
        for (int vertcheck = r - 1; vertcheck >= 0 && Data[vertcheck][c] == Turningplayer; vertcheck--, vertical++);
        if (vertical > 3) {
            GameOver = true;
            Result = (Turningplayer == PlayerChar[0]) ? -1 : 1;
            return true;
        }

        // Horizontal check
        int horizontal = 1;
        for (int horcheck = c - 1; horcheck >= 0 && Data[r][horcheck] == Turningplayer; horcheck--, horizontal++);
        for (int horcheck = c + 1; horcheck <= 6 && Data[r][horcheck] == Turningplayer; horcheck++, horizontal++);
        if (horizontal > 3) {
            GameOver = true;
            Result = (Turningplayer == PlayerChar[0]) ? -1 : 1;
            return true;
        }

        // Diagonal 1 check
        int diagonal1 = 1;
        for (int vertcheck = r - 1, horcheck = c - 1; vertcheck >= 0 && horcheck >= 0 && Data[vertcheck][horcheck] == Turningplayer; diagonal1++, vertcheck--, horcheck--);
        for (int vertcheck = r + 1, horcheck = c + 1; vertcheck <= 5 && horcheck <= 6 && Data[vertcheck][horcheck] == Turningplayer; diagonal1++, vertcheck++, horcheck++);
        if (diagonal1 > 3) {
            GameOver = true;
            Result = (Turningplayer == PlayerChar[0]) ? -1 : 1;
            return true;
        }

        // Diagonal 2 check
        int diagonal2 = 1;
        for (int vertcheck = r - 1, horcheck = c + 1; vertcheck >= 0 && horcheck <= 6 && Data[vertcheck][horcheck] == Turningplayer; diagonal2++, vertcheck--, horcheck++);
        for (int vertcheck = r + 1, horcheck = c - 1; vertcheck <= 5 && horcheck >= 0 && Data[vertcheck][horcheck] == Turningplayer; diagonal2++, vertcheck++, horcheck--);
        if (diagonal2 > 3) {
            GameOver = true;
            Result = (Turningplayer == PlayerChar[0]) ? -1 : 1;
            return true;
        }

        return false;
    }

    return false;
}



}

    string PlayerNames[2]; // To Hold Name of Players Who are playing
    int TurningPlayer=1; // To save the players ID who is making a move; 0: First Player, 1: Second Player
    char PlayerChar[2]; // Characters to be shown for move
    char PlayerWinningChar[2]; // Character to be shown if player wins.
    int  ColumnMoves[7]; // An array to keep record of first empty cell in a column
    char Data[6][7]; // Array to hold game data.
    bool GameOver; // If true it means the game is over.
    int Result;// Variable to hold result of game {0: Drawn, -1: First Player Lost, 1: First Player Won}
    int row,col;
};


int main(){
    /*
        This function use a single variable of type connect4
        and use it's functions to play the game
    */
    int x;
    string N[2]={};
    connect4 Game(N);
    cout<<"                                             Welcome To Connect-4                                                          "<<endl;
    cout<<"To Start Playing PRESS 1"<<endl;
    cin>>x;
    int columnss;
    int y=0;
    int Turn=0;
    while(x==1)
    {
        cout<<"Enter the name of the First Player"<<endl;
        cin>>N[0];
        cout<<"Enter the name of the Second Player"<<endl;
        cin>>N[1];
        Game.ShowGame();
        while(Turn<=42)
        {
            if(y%2 == 0)
            {
                y=0;
            }
            else
            {
                y=1;
            }
            cout<<"Its "<<(N[y])<< " Turn "<<endl;
            cout<<"Enter the Column : "<<endl;
            y++;
            cin>>columnss;
            Turn++;
            if(columnss>0 && columnss<8)
            {
                Game.MakeMove(columnss);
                Game.ShowGame();
                Game.isGameOver();
                if(Turn==42)
                {
                    cout<<" Its a draw ";
                    return 0;
                }
            }
            else
            {
                cout<<"Enter a valid value for column!!"<<endl;
                y--;
                Turn--;
            }
        }
        cout<<endl<<endl<<"To Start Playing Again PRESS 1 or PRESS 0 to Abort And To Restart PRESS 2"<<endl;
        cin>>x;
        if(x==2)
        {
            Game.re_init(N);
            cout<<"Game has been Reset "<<endl;
            cout<<"To Start Playing  PRESS 1 or PRESS 0 to Abort"<<endl;
            cin>>x;
        }

    }
    cout<<" Game Aborted ";



    return 0;
}
