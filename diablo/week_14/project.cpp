#include <ncurses.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

class State
{
private:
    int x;
    int y;
    int turn;
    std::vector<std::vector<bool>> obstacles;
    void spawn_obstacle();

public:
    State(int width, int height);
    void right(int units);
    void left(int units);
    void up(int units);
    void down(int units);
    int update();
    void print();
    void end();
};

State::State(int width, int height)
{
    x = 0;
    y = 0;
    turn = 0;
    std::vector<std::vector<bool>> a(height, std::vector<bool>(width, false));
    obstacles = a;
}

void State::right(int units)
{
    if (x + units <= obstacles[0].size() - 1)
    {
        x += units;
    }
}

void State::left(int units)
{
    if (x - units >= 0)
    {
        x -= units;
    }
}

void State::up(int units)
{
    if (y - units >= 0)
    {
        y -= units;
    }
}

void State::down(int units)
{
    if (y + units <= obstacles[0].size() - 1)
    {
        y += units;
    }
}

int State::update()
{
    if (turn % 5 == 0)
    {
        // check for failing state
        if (obstacles[y][x])
        {
            return -1;
        }
        for (int i = 0; i < obstacles.size(); i++)
        {
            // shift obstacles left one
            obstacles.at(i).erase(obstacles.at(i).begin());
            obstacles.at(i).push_back(false);
        }
    }
    // spawn obstacle
    if (turn % 15 == 0)
    {
        spawn_obstacle();
    }
    turn += 1;
    return 0;
}

void State::print()
{
    for (int i = 0; i < obstacles.size(); i++)
    {
        for (int j = 0; j < obstacles[i].size(); j++)
        {
            if (obstacles[i][j])
            {
                mvprintw(i, j, "X");
            }
            else
            {
                mvprintw(i, j, " ");
            }
        }
    }
    mvprintw(y, x, ">");
    // print turn
    mvprintw(0, 0, "%d", turn);
    refresh();
}

void State::spawn_obstacle()
{
    int r = rand() % obstacles.size();
    obstacles[r][obstacles[r].size() - 1] = true;
}

void State::end()
{
    clear();
    printw("Game Over\nScore: %d", turn);
    timeout(-1);
    getch();
}

int main()
{
    int input;
    initscr();
    timeout(10);

    State state(100, 30);
    srand(time(NULL));

    for (;;)
    {
        if ((input = getch()) != ERR)
        {
            switch (input)
            {
            case 65:
                state.up(1);
                break;
            case 66:
                state.down(1);
                break;
            case 68:
                state.left(1);
                break;
            case 67:
                state.right(1);
                break;
            default:
                break;
            }
        }

        if (state.update() < 0)
        {
            break;
        }
        state.print();
    }
    state.end();
    endwin();
    return 0;
}