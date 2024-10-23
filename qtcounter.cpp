#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// function for checking the axis of a certain move
bool isSameAxis(const string& move1, const string& move2) {
    char axis1 = move1[0];
    char axis2 = move2[0];
    
    // Check if on same axis and adjacent (including opposite direction)
    return ( (axis1 == 'U' || axis1 == 'D') && (axis2 == 'U' || axis2 == 'D') ) ||
           ( (axis1 == 'F' || axis1 == 'B') && (axis2 == 'F' || axis2 == 'B') ) ||
           ( (axis1 == 'R' || axis1 == 'L') && (axis2 == 'R' || axis2 == 'L') );
}

int main() {
    
    // Map to group moves by the count of moves without '2'
    std::map<int, std::vector<std::string>> groupedMoves;
    std::string input; // To store the entire input

    // Get user input
    cout << "Paste your moves separated by spaces, one line at a time. Enter a blank line to finish." << endl;
    getline(cin, input); // Get the first line
    while (!input.empty()) {
        std::stringstream s(input); // Convert the line into a stringstream
        std::vector<std::string> moves; // To store the moves in the row
        
        // Split the line by spaces
        std::string solution;
        while (getline(s, solution, ' ')) {
            moves.push_back(solution); // Add each move to the row
        }
        int count = 0;
        std::string originalMoves;
        string lastMove; // To store the last counted move
        for (const auto& move : moves) {
            originalMoves += move + " "; // store the moves for printing
            if (move.find('2') == string::npos) { // Check if move does not contain '2'
                if (!isSameAxis(lastMove, move)) {
                    count++;
                    lastMove = move; // Update lastMove after counting the move
                } else if (isSameAxis(lastMove, move)) {
                    count--;
                    lastMove = move;
                }
            } 
            else {
                lastMove.clear(); // Reset lastMove only if the current move has '2'
            }
        }
        
        // Trim the trailing space from originalMoves
        if (!originalMoves.empty()) {
            originalMoves.pop_back();
        }
        
        // Add the row to the map, grouped by count
        groupedMoves[count].push_back(originalMoves);
        // Get the next line of input
        getline(cin, input); 
    }
    
    // Print the grouped moves, sorted by the count
    for (const auto& entry : groupedMoves) {
        std::cout << entry.first << " quarter turns -\n"; // Print the count
        for (const auto& moves : entry.second) {
            std::cout << moves << std::endl; // Print the moves corresponding to the count
        }
        std::cout << std::endl; // Add a newline for better readability
    }
    return 0;
}
