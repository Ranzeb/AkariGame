#ifndef AKARI_H
#define AKARI_H

#include <vector>
#include <complex>
#include "game.h"

using namespace std;

class Akari : public Game
{
public:
    Akari();
    void play_at(int x, int y);
    string get_val(int x, int y);
    bool finished();
    string to_string();

    int cols() {return cols_; }
    int rows() { return rows_; }
    string message() { return "Puzzle solved"; }
    void fill_lights(int x,int y);
    void reset_lights(int x,int y);
    bool find_bulb(int x,int y);
    bool is_full();
    bool controllo_finale(int y, int x,char val);
    void luce(int x,int y,int posX,int posY);

    void load(string name);
    void save(string name);

    static const char EMPTY = ' ';
    static const char BULB  = '@';
    static const char FLAG  = 'x';
    static const char LIGHT = '+';
    static const char WALL0 = '0';
    static const char WALL1 = '1';
    static const char WALL2 = '2';
    static const char WALL3 = '3';
    static const char WALL4 = '4';
    static const char WALL  = '5';



private:
    int cols_ = 7;
    int rows_ = 7;
    bool set_flag = false;
    vector< vector<char> > board_ = {
        {' ', ' ', ' ', '5', '5', '1', ' '},
        {' ', '5', ' ', ' ', ' ', ' ', ' '},
        {'1', ' ', ' ', '5', ' ', '0', ' '},
        {' ', '5', ' ', ' ', ' ', '5', ' '},
        {' ', '1', ' ', '3', ' ', ' ', '2'},
        {' ', ' ', ' ', ' ', ' ', '2', ' '},
        {' ', '5', '5', '5', ' ', ' ', ' '} };
    // '5' is for unnumbered walls:
    // no constraint on surrounding bulbs
};

#endif // AKARI_H
