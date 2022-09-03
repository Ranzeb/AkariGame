#include "akari.h"
#include <fstream>

//poi togli serve solo per stampare a schermo le prove
#include <iostream>
using namespace std;

vector<vector<int>> dirs4 = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

Akari::Akari()
{

}

//funzione per caricare partita da file
void Akari::load(string name)
{
    ifstream file{name};  // file input stream
    if (file.good()) {            // is stream available?

        for (int y = 0; y < rows_; ++y) {
            for (int x = 0; x < cols_; ++x) {
                file >> board_[y][x];
            }
        }
    }
    file.close();

}


//funzione per salvare partita su file
void Akari::save(string name)
{
    ofstream file{name};  // file output stream
    if (file.good()) {            // is stream available?

        for (int y = 0; y < rows_; ++y) {
            for (int x = 0; x < cols_; ++x) {
                 file <<"[" << board_[y][x] << " ";
            }
            file << "\n";
        }
    }
    file.close();
}


//riempie le righe e le colonne con la luce
void Akari::fill_lights(int x,int y)
{
    for(int i = x+1; i <= cols_;i++) // riempio a destra
    {
        if(board_[y][i] == ' ' || board_[y][i] == '+' || board_[y][i] == 'x')
            board_[y][i] = LIGHT;
        else i = cols_; // esco dal ciclo se trovo un muro o una cella illuminata
    }

    for(int i = x-1; i >= 0;i--)  // riempio a sinistra
    {
        if(board_[y][i] == ' ' || board_[y][i] == '+' || board_[y][i] == 'x')
            board_[y][i] = LIGHT;
        else i = 0; // esco dal ciclo se trovo un muro o una cella illuminata
    }

    for(int i = y+1; i <= rows_;i++) // riempio sotto
    {
        if(board_[i][x] == ' ' || board_[i][x] == '+' || board_[i][x] == 'x')
            board_[i][x] = LIGHT;
        else i = rows_; // esco dal ciclo se trovo un muro o una cella illuminata

    }

    for(int i = y-1; i >= 0;i--) // riempio sopra
    {
        if(board_[i][x] == ' ' || board_[i][x] == '+' || board_[i][x] == 'x')
            board_[i][x] = LIGHT;
        else i = 0; // esco dal ciclo se trovo un muro o una cella illuminata

    }

}


// cerco se una cella è illuminata da altre lampadine
bool Akari::find_bulb(int y, int x)
{
    for(int i = x+1; i <= cols_;i++) // controllo a destra
    {
        if(board_[y][i] == '@')
            return true;
        else if(board_[y][i] != '@' && board_[y][i] != ' ' && board_[y][i] != '+')
            i = cols_;

    }

    for(int i = x-1; i >= 0;i--)  // controllo a sinistra
    {
        if(board_[y][i] == '@')
            return true;
        else if(board_[y][i] != '@' && board_[y][i] != ' ' && board_[y][i] != '+')
            i = 0;
    }

    for(int i = y+1; i <= rows_;i++) // controllo sotto
    {
        if(board_[i][x] == '@')
            return true;
         else if(board_[i][x] != '@' && board_[i][x] != ' ' && board_[i][x] != '+')
             i = rows_;
    }

    for(int i = y-1; i >= 0;i--) // controllo sopra
    {
        if(board_[i][x] == '@')
            return true;
        else if(board_[i][x] != '@' && board_[i][x] != ' ' && board_[i][x] != '+')
            i = 0;
    }

    return false;
}


//rimuove la luce alla rimozione della lampada
void Akari::reset_lights(int x,int y)
{
    for(int i = x+1; i <= cols_;i++)
    {
       if(board_[y][i] == '+')
       {
            if(find_bulb(y,i) == false)
                board_[y][i] = EMPTY;
       }
       else i = cols_; // esco dal ciclo se trovo un muro
    }

    for(int i = x-1; i>=0;i--)
    {
        if(board_[y][i] == '+')
        {
            if(find_bulb(y,i) == false)
                board_[y][i] = EMPTY;
        }
        else i = 0; // esco dal ciclo se trovo un muro
    }

    for(int i = y+1; i<= rows_;i++)
    {
        if(board_[i][x] == '+')
        {
            if(find_bulb(i,x) == false)
                board_[i][x] = EMPTY;
        }
        else i = rows_;

    }

    for(int i = y-1; i>= 0;i--)
    {
        if(board_[i][x] == '+')
        {
             if(find_bulb(i,x) == false)
                board_[i][x] = EMPTY;
        }
        else i = 0;

    }

}

void Akari::luce(int x,int y,int dirX,int dirY)
{
    int posX = x + dirX;
    int posY = y + dirY;


        while(board_[posY][posX] == EMPTY || board_[posY][posX] == LIGHT)
        {
            if (0 <= posY && posY < rows_ && 0 <= posX && posX < cols_)
            {
                board_[posY][posX] = LIGHT;
                posX += dirX;
                posY += dirY;
            }
        }

}


void Akari::play_at(int x, int y)
{
    if (0 <= x && x < cols_ && 0 <= y && y < rows_){
        //setto la luce
        if(board_[y][x] == ' ')  //Andrebbe tolta la copertura così
           board_[y][x] = FLAG;
        else if(board_[y][x] == 'x' || board_[y][x] == ' ')
        {
            board_[y][x] = BULB;
            luce(x,y,-1,0);
            luce(x,y,0,1);
            luce(x,y,+1,0);
            luce(x,y,0,-1);
        }

        else if(board_[y][x] == '@')
        {
            board_[y][x] = EMPTY;
            reset_lights(x,y);
        }

    }
}


std::string Akari::get_val(int x, int y)
{

    if (0 <= x && x < cols_ && 0 <= y && y < rows_) {
        //return to_string(board_[y][x]) + to_string(cover_[y][x]);

        // Visualizzazione matrice GUI
        string txt = string(1, board_[y][x]);
        return txt;


    }
    return " ";
}


bool Akari::is_full() //controllo se la matrice è piena, caselle illuminate o con bulb
{
    for (int y = 0; y < rows_; ++y) {
        for (int x = 0; x < cols_; ++x) {
            if (board_[y][x] == ' ' || board_[y][x] == 'x' ) {
                return false;
            }
        }
    }
    return true;
}

bool Akari::controllo_finale(int y, int x, char val)
{
    int counter = 0;

    if(x-1 >= 0)
    {   cout<<"entrato";
        if(board_[y][x-1] == '@')
            counter++;
    }

    if(x+1 <= cols_ )
    {   cout<<"entrato2";
        if(board_[y][x+1] == '@')
            counter++;
    }

    if(y-1 >= 0 )
    {   cout<<"entrato3";
        if(board_[y-1][x] == '@')
            counter++;
    }

    if(y+1 <= rows_ )
    {   cout<<"entrato4";
        if(board_[y+1][x] == '@')
            counter++;
    }

    if ((char)counter == val)
        return true;
    else
        return false;


}

bool Akari::finished()
{
    // conversion from char to int
    // char val = '4';  /* just for example ... */
    // int num = val - '0';
    
    /* ADD YOUR CODE HERE */

    if(is_full())
    {
        for (int y = 0; y < rows_; ++y)
        {
            for (int x = 0; x < cols_; ++x)
            {
                if (board_[y][x] >= '0' && board_[y][x] <= '4')
                {
                    if(controllo_finale(y,x,board_[y][x]) == false)
                        cout<<"entrato nel controllo"<<endl;
                        return false;
                }


            }

        }
        return true;
    }
}

string Akari::to_string()
{
    /* ADD YOUR CODE HERE */
    return "";
}
