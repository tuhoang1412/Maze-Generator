// Author: Tu Hoang
/*
 * Maze Generator: it uses DFS algorithm to find a random unique path through a square and form a maze as the result.
 * 'X' represents the wall or border, and the empty spaces represents that path that the algorithm chose.
 */
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

// Randomize engine
static mt19937 mt(time(nullptr));

// Class for maze
class Maze
{
    // Position for x, y coordinates in 2D array
    // It holds value as ' ' or 'X'. Also, keeping track of being visited
    struct position
    {
        int x{}, y{};

        string data;

        bool isVisited;

        position() = default;

        position(int x_pos, int y_pos, string data, bool status) : x(x_pos), y(y_pos), data(move(data)), isVisited(status) {}
    };
    int mazeSize{};
    // 2D array skeleton for the square
    vector<vector<position>> skeleton;

public:
    Maze() = default;
    Maze(int size)
    {
        mazeSize = size * 2 - 1;
        skeleton = initMaze(this->mazeSize);
    }
    // Print out the maze in a formatted way
    void printMaze()
    {
        for (int i = 0; i < this->mazeSize + 2; i++)
        {
            cout << "X  ";
        }
        for (const vector<position> &row : skeleton)
        {
            cout << "\nX  ";
            for (const position &entry : row)
            {
                cout << entry.data << "  ";
            }
            cout << "X";
        }
        cout << "\nX";
        for (int i = 0; i < this->mazeSize + 1; i++)
        {
            cout << "  X";
        }
    }
    // Initializing the maze 2D array filled with 'X'
    vector<vector<position>> initMaze(int size)
    {
        vector<position> row(size, position(-1, -1, "X", false));
        vector<vector<position>> maze(size, row);
        for (int i = 0; i < size; i += 2)
        {
            for (int j = 0; j < size; j += 2)
            {
                maze[i][j].x = i;
                maze[i][j].y = j;
            }
        }
        return maze;
    }
    // Getting unvisited adjacent positions. And from those, pick a random one to proceed
    vector<position> getAdjacent(const position &current_pos)
    {
        vector<position> v;

        for (int *off : (int[4][2]){{0, 2}, {2, 0}, {0, -2}, {-2, 0}})
        {
            int idx_x = off[0] + current_pos.x;
            int idx_y = off[1] + current_pos.y;

            if (0 <= idx_x && idx_x <= this->mazeSize - 1 && 0 <= idx_y && idx_y <= this->mazeSize - 1 && !this->skeleton[idx_x][idx_y].isVisited)
            {

                v.push_back(this->skeleton[idx_x][idx_y]);
            }
        }
        // Shuffle the unvisited neighbors
        if (v.size() > 1)
        {
            shuffle(v.begin(), v.end(), mt);
        }
        return v;
    }
    // Switching the value of the current position from 'X' to ' ' as this position is in the path
    void breakWall(const position &current_pos, const position &next_pos)
    {
        this->skeleton[next_pos.x][next_pos.y].data = " ";
        this->skeleton[(next_pos.x + current_pos.x) / 2][(current_pos.y + next_pos.y) / 2].data = " ";
    }
    // Utilizing DFS algorithm to move to the next unvisited positions
    bool moveNext(position &current_pos)
    {
        if (this->skeleton[current_pos.x][current_pos.y].isVisited)
            return false;
        else
            this->skeleton[current_pos.x][current_pos.y].isVisited = true;

        vector<position> adj = getAdjacent(current_pos);
        if (!adj.empty())
        {
            for (position &nextMove : adj)
            {
                if (moveNext(nextMove))
                {
                    breakWall(current_pos, nextMove);
                }
            }
        }
        return true;
    }
    // Driver thats initializing the starting position and generating the maze
    void generateMaze()
    {
        // Bottom left corner position is starting position
        position &starting_pos = this->skeleton[this->mazeSize - 1][0];
        starting_pos.data = " ";
        moveNext(starting_pos);
    }
};

int main(int argc, char *argv[])
{
    // Getting the command line argument as init size
    //  or 8 by default
    int initSize = argc > 1 ? stoi(argv[1]) : 8;

    Maze m(initSize);
    // Building the maze
    m.generateMaze();
    // Print out the maze
    m.printMaze();

    return 0;
}
