/*
    Andrewfied Maze Escape

    Sometimes when dealing with graphs, it is easiest to leave it in its input format 
    rather than creating another structure like an adjacency list/matrix. You are given 
    a graph represented as a vector of strings. Write a function 
    `traverse(vector<string>& graph)` that takes as input a graph and returns the length 
    of the shortest path between vertices `s` and `t`. If no path exists between `s` and 
    `t`, then return `-1`. The details of the graph as a vector of strings are as follows:

    1. The start position is represented by a 's' and will always be the first character of 
       the first string (`graph[0][0]`). 
    2. The end position is represented by a 't' and will always be the last character of the 
       final string (`graph[graph.size()-1][graph[0].length()-1]`).
    3. A '.' character represents a normal vertex in the graph.
    4. A '#' character represents that you cannot visit this vertex in the graph (or there 
       is no vertex at this position).
    5. Adjacent vertices are those immediately horizontal or vertical from the current vertex 
       (diagonal moves are not allowed).
    6. The cost of moving along one edge (from one vertex to an adjacent vertex) is always 1 
       (i.e. this is an unweighted graph).

    Sample Input
        s#.#.   
        .#...  
        ...#t    

    Sample Output: 8
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int shortestPath(std::vector<std::string>& graph)
{
    int rows = graph.size();
    int cols = graph[0].size();
    vector<std::vector<int>> dp(rows, vector<int>(cols, 99));
    dp[0][0] = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 && j == 0) {}
            else {
                if (graph[i][j] == '#')
                    continue;
                if (i == 0) {
                    dp[i][j] = dp[i][j - 1];
                }
                else if (j == 0) {
                    dp[i][j] = dp[i - 1][j];
                }
                else {
                    dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]);
                }
                if (dp[i][j] != 99 && graph[i][j] != 't') {
                    dp[i][j] += '1' - '0';
                }
            }
        }
    }

    if (dp[rows - 1][cols - 1] == 99) { // we didn't find the path
        //loop through again and base values on all adjacents

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (i == 0 && j == 0) {}
                else {
                    int top = 0;
                    int bot = 0;
                    int right = 0;
                    int left = 0;
                    if (dp[i][j] == 99 && graph[i][j] != '#') {
                        if (i == 0 && j + 1 < dp[0].size()) { // there is no top; first checks if there is a right
                            bot = dp[i + 1][j];
                            right = dp[i][j + 1];
                            left = dp[i][j - 1];
                            int min1 = min(min(bot, right), left);
                            dp[i][j] = min1 + 1;
                        }
                        else if (i == 0) {
                            bot = dp[i + 1][j];
                            left = dp[i][j - 1];
                            int min1 = min(bot, left);
                            dp[i][j] = min1 + 1;
                        }
                        else if (j == 0 && i == dp.size() - 1) { // there is no left and no bottom
                            right = dp[i][j + 1];
                            top = dp[i - 1][j];
                            int min1 = min(min(bot, right), top);
                            dp[i][j] = min1 + 1;
                        }
                        else if (j == 0) {
                            bot = dp[i + 1][j];
                            right = dp[i][j + 1];
                            top = dp[i - 1][j];
                            int min1 = min(min(bot, right), top);
                            dp[i][j] = min1 + 1;
                        }
                        else if (j == dp[0].size() - 1 && i == dp.size() - 1) { // there is no right and no bottom
                            top = dp[i - 1][j];
                            left = dp[i][j - 1];
                            int min1 = min(left, top);
                            dp[i][j] = min1 + 1;
                        }
                        else if (j == dp[0].size() - 1) { // there is no right
                            top = dp[i - 1][j];
                            left = dp[i][j - 1];
                            bot = dp[i + 1][j];
                            int min1 = min(min(bot, left), top);
                            dp[i][j] = min1 + 1;
                        }
                        else if (i == graph.size() - 1) {// there is no bottom
                            right = dp[i][j + 1];
                            left = dp[i][j - 1];
                            top = dp[i - 1][j];
                            int min1 = min(min(left, right), top);
                            dp[i][j] = min1 + 1;
                        }
                        else { // we have all 4
                            bot = dp[i + 1][j];
                            right = dp[i][j + 1];
                            top = dp[i - 1][j];
                            left = dp[i][j - 1];
                            int min1 = min(min(right, left), min(top, bot));
                            dp[i][j] = min1 + 1;
                        }
                    }
                }
            }
        }
    }
    else {
        dp[rows - 1][cols - 1] += 1;
    }

    

    return dp[rows - 1][cols - 1] == 99 ? -1 : dp[rows - 1][cols - 1];
}

int traverse(std::vector<std::string>& graph)
{
    int path = shortestPath(graph);

    /*char start = graph[0][0]; // 's'
    char finish = graph[graph.size() - 1][graph[0].length() - 1]; // 't'
    int minPath = 0;
    pair<int, int> curr(0, 0);
    // run the length of the string and find whether 
        // first check horizontal, if not go down(increase i)
            // if we can't go down anymore, go up(decrease i)
            // repeat
            // graph[x] is a string
    // may have to change to a while loop, while curr != t\

    // what if i just reverse the actions when it doesn't work

    int i = 0;
    int j = 1;
    while (graph[curr.first][curr.second] != finish) {
        while (j < graph[0].length() + 1) {
            if (graph[i][j] != '#' && j < graph[0].length()) {
                //curr.first = i;
                curr.second = j;
                j = curr.second + 1;
                minPath++;
            }
            else if (graph[i][j] != '#' && j == graph[0].length()) { // when we reached the end
                i++; // go down
                curr.first = i;
                minPath++;
                j = curr.second + 1;
                break;
            }
            else if (graph[i][j] == '#' && i < graph.size() - 1) { // checks down first
                i++; // go down
                curr.first = i;
                minPath++;
                j = curr.second + 1;
                break; // get out of loop; if this doesn't work try making it equal curr.second +1
            }
            else if (graph[i][j] == '#') {
                i--; // go up
                curr.first = i;
                minPath++;
                j = curr.second + 1;
                break;
            }
        }
    }*/

    if (path >= 99) {
        return -1;
    }
    return path;
}
