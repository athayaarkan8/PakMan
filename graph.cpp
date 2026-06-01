#include <iostream>
using namespace std;

void renderMaze(int maze[5][5]) {

    cout << "\n=== MAZE ===\n";

    for(int i = 0; i < 5; i++) {

        for(int j = 0; j < 5; j++) {

            if(maze[i][j] == 1)
                cout << "# ";
            else
                cout << ". ";
        }

        cout << endl;
    }
}