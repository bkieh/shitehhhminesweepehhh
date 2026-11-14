#include <iostream>
#include <array>
#include <random>
#include <string>
std::vector<std::vector<int>> createBombs(const int w,  const int h, int& bombCount) {
	std::vector<std::vector<int>> bombGrid;
	std::random_device rd;  
	std::mt19937 eng(rd());  
	std::uniform_int_distribution<> distr(1, 20); 
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (!(distr(eng) % 10)) {
				std::vector<int> bombLocation = {i, j};
				bombGrid.push_back(bombLocation);
				bombCount++;

			}


		}

	}

	return bombGrid;
	



}
void countBombs(auto& grid, int x, int y, int w, int h) {
	
	std::vector<int> dY = {-1, -1, -1, 0, 0, 1, 1, 1}; // possible Y direction
	std::vector<int> dX = {-1, 0, 1, -1, 1, -1, 0, 1}; // possible X direction
	for (int i = 0; i < 8; i++) {
		int nY = y + dY[i];
		int nX = x + dX[i];
		

		if ( (nY >= 0 && nY < h)  && (nX >= 0 && nX < w)) {
			if (grid[nY][nX] != -1) {
			grid[nY][nX] += 1; 
			}
		}


	}
	

}

void translateBombs(std::vector<std::vector<int>>& grid, const std::vector<std::vector<int>>& bombGrid, int w, int h ) {
	for (const auto& loc : bombGrid) {
		int x = loc[0];
		int y = loc[1];
		grid[y][x] = -1;
	}
	for (const auto& loc : bombGrid) {
		countBombs(grid, loc[0], loc[1], w, h);
		

	}

	




}

void printGrid(const auto& grid, const int& w, const int& h, const int& bombCount) {
    std::cout << "Generated Grid (" << w << "x" << h << ", Bomb Count: " << bombCount << "):\n";
    std::cout << "   "; // offset to align with the Y-axis numbers
    for (int c = 0; c < w; c++) {
        if (c < 10) {
            std::cout << " " << c << "  "; // 3 characters wide for single digits (e.g., " 0 ")
        } else {
            std::cout << "" << c << "  ";  // 3 characters wide for double digits (e.g., "10 ")
        }
    }
    std::cout << "\n";
    for (int r = h - 1; r >= 0; r--) {
		if (r < 10) {
            std::cout << " " << r << " ";
        } else {
            std::cout << r << " ";
        }
	
        for (int c = 0; c < w; c++) {
                std::cout << "[ ] ";
        }
        std::cout << "\n";
    }
    

}

void printGrid(const auto& grid, const auto& fGrid, const int& w, const int& h) {
	std::cout << "Generated Grid (" << w << "x" << h << "):\n";
	std::cout << "   "; // offset to align with the Y-axis numbers
    for (int c = 0; c < w; c++) {
         if (c < 10) {
            std::cout << " " << c << "  "; // 3 characters wide for single digits (e.g., " 0 ")
        } else {
            std::cout << "" << c << "  ";  // 3 characters wide for double digits (e.g., "10 ")
        }
    }
    std::cout << "\n";
	
    for (int r = h - 1; r >= 0; r--) {
	if (r < 10) {
            std::cout << " " << r << " ";
        } else {
            std::cout << r << " ";
        }
	
        for (int c = 0; c < w; c++) {
            if (fGrid[r][c] == -2) { // if flagged
		std::cout << "[f] ";
	    } else if (fGrid[r][c] == 1) { // if the number is visible
                std::cout << "[" << grid[r][c] << "] ";
            } else {
		std::cout << "[ ] ";
	    }
        }
        std::cout << "\n";
    }
    

}


void createGrid (auto& grid, const int& w, const int& h, int& bombCount) {

	auto bombGrid = createBombs(w,h,bombCount);
	translateBombs(grid, bombGrid, w, h);

	printGrid(grid, w, h, bombCount);

	



		
	

}

void flagLoc(auto& grid, auto& fGrid, const int& x, const int& y, const int& w, const int& h) {
	 
	if (x >= 0  && x < w && y < h && y >= 0) {
		if(fGrid[y][x] != 1) {
			if(fGrid[y][x] == -2) {
				fGrid[y][x] = 0;
			} else {
				fGrid[y][x] = -2; // -2 because -1 stands for bombed and even though its different maps the distinction will probably save me time, and it can't be a positive number for the same reason
			}
		}

		

	}

	printGrid(grid, fGrid, w, h);

}

void stepLoc (auto& grid, auto& fGrid, const int& x, const int& y, const int& w, const int& h, bool& hasLost) {
	if(x >= 0  && x < w && y < h && y >= 0){
		if(fGrid[y][x] == 0) {
			fGrid[y][x] = 1;
			if (grid[y][x] == -1) {
			hasLost = true;
			}
			if (grid[y][x] == 0) {
				std::vector<int> dY = {-1, -1, -1, 0, 0, 1, 1, 1}; // possible Y direction
				std::vector<int> dX = {-1, 0, 1, -1, 1, -1, 0, 1}; // possible X direction
				for (int i = 0; i < 8; i++) {
					int nY = y + dY[i];
					int nX = x + dX[i];
					stepLoc(grid, fGrid, nX, nY, w, h, hasLost);

					

				}
			}
		}

	}
	printGrid(grid, fGrid, w, h);
	
	
}

void promptUser (auto& grid, auto& fGrid, const int& w, const int& h, bool& hasLost, bool& hasWon) {
	std::string key;
	std::cout << "[F]lag, or [S]tep? \n";
	std::getline(std::cin, key);
	if(key == "F") {
		std::cout << "Flag Where (X-coords)? (Input numbers within the " << w << "x" << h << "grid)\n";
		int x;
		int y;
		std::string placeholder;
		std::getline(std::cin, placeholder);
		x = std::stoi(placeholder);
		std::cout << "Flag Where (Y-coords)? (Input numbers within the " << w << "x" << h << "grid)\n";
		std::getline(std::cin, placeholder);
		y = std::stoi(placeholder);
		flagLoc(grid, fGrid, x, y, w, h);
	} else if (key == "S") {
		std::cout << "Step Where (X-coords)? (Input numbers within the " << w << "x" << h << "grid)\n";
		int x;
		int y;
		std::string placeholder;
		std::getline(std::cin, placeholder);
		x = std::stoi(placeholder);
		std::cout << "Step Where (Y-coords)? (Input numbers within the " << w << "x" << h << "grid)\n";
		std::getline(std::cin, placeholder);
		y = std::stoi(placeholder);
		stepLoc(grid, fGrid, x, y, w, h, hasLost);
	}

}




int main () {
	int bombCount = 0;
	int h = 20;
	int w = 20;
	bool hasWon = false;
	bool hasLost = false;
	/*
	 * Initialization of the Minesweeper Grid
	 * Firstly, creates bombs via CreateBombs() -> translateBombs() -> createGrid() -> printGrid()
	 *
	 *
	 * */

	std::vector<std::vector<int>> grid;
	grid = std::vector<std::vector<int>>(h, std::vector<int>(w, 0));
	
	createGrid(grid, w, h, bombCount);
	

	std::vector<std::vector<int>> fGrid;
	fGrid = std::vector<std::vector<int>>(h, std::vector<int>(w, 0)); // fGrid stands for flaggedGrid
	while (!(hasWon || hasLost)) {
		promptUser(grid, fGrid, w, h, hasLost, hasWon);

	}

}
