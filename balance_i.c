#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct Move
{
    int d;
    int pos;
};
typedef struct Move Move;


void minimax(bool is_A_turn, int path_length);
int get_d(int path[], int path_length);
Move min(int alpha, int beta, int path[], int path_length, bool first_move);
Move max(int alpha, int beta, int path[], int path_length, bool first_move);


int main(void)
{
    for (int i = 1; i <= 100; i++)
    {
        printf("P%i\n", i);
        minimax(false, i);
    }

    return 0;
}


int get_d(int path[], int path_length)
{
    // get edges
    int edges[path_length - 1];
    for (int i = 0; i < path_length - 1; i++)
    {
        edges[i] = path[i] ^ path[i+1];
    }

    // compute d
    int d = 0;
    for (int j = 0; j < path_length - 1; j++)
    {
        if (edges[j] == 0)
            d--;
        else
            d++;
    }

    return d;

}


Move min(int alpha, int beta, int path[], int path_length, bool first_move)
{
    Move a_move;
    int minv = 1000;
    
    // check if path fully labeled (i.e. game over)
    bool game_over = true;
    for (int i = 0; i < path_length; i++)
    {
        if (path[i] == 2)
        {
            game_over = false;
            break;
        }
    }

    if (game_over)
    {
        a_move = (Move){.d = get_d(path, path_length), .pos = 0};
        return a_move;
    }


    // if first move, only evaluate potential moves on first half of path (by symmetry)
    int options;
    if (first_move)
        options = path_length / 2 + 1;
    else
        options = path_length;

    for (int j = 0; j < options; j++)
    {
        if (path[j] == 2)
        {
            path[j] = 0;

            Move i_move = max(alpha, beta, path, path_length, false);
            if (i_move.d < minv)
            {
                minv = i_move.d;
                a_move.pos = j;
            }

            if (minv < beta)
                beta = minv;
            
            path[j] = 2;

            if (beta <= alpha)
                break;
        }
    }

    a_move.d = minv;
    return a_move;
}


Move max(int alpha, int beta, int path[], int path_length, bool first_move)
{
    Move i_move;
    int maxv = -1000;
    
    // check if path fully labeled (i.e. game over)
    bool game_over = true;
    for (int i = 0; i < path_length; i++)
    {
        if (path[i] == 2)
        {
            game_over = false;
            break;
        }
    }

    if (game_over)
    {
        i_move = (Move){.d = get_d(path, path_length), .pos = 0};
        return i_move;
    }


    // if first move, only evaluate potential moves on first half of path (by symmetry)
    int options;
    if (first_move)
        options = path_length / 2 + 1;
    else
        options = path_length;

    for (int j = 0; j < options; j++)
    {
        if (path[j] == 2)
        {
            path[j] = 1;

            Move a_move = min(alpha, beta, path, path_length, false);
            if (a_move.d > maxv)
            {
                maxv = a_move.d;
                i_move.pos = j;
            }

            if (maxv > alpha)
                alpha = maxv;
            
            path[j] = 2;

            if (alpha >= beta)
                break;
        }
    }

    i_move.d = maxv;
    return i_move;
}


void minimax(bool is_A_turn, int path_length)
{
    // initialize path to all 2s
    int path[path_length];
    for (int i = 0; i < path_length; i++)
    {
        path[i] = 2;
    }
    bool first_move = true;
    
    Move move;
    if (is_A_turn)
    {
        move = min(-1000, 1000, path, path_length, first_move);
        printf("d = %i\n", move.d);
    }
    else
    {
        move = max(-1000, 1000, path, path_length, first_move);
        printf("d = %i\n", move.d);
    }
}