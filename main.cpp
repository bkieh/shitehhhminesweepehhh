#include <iostream>
#include <array>
#include <random>
#include <string>
enum DIFFICULTY {
	Baby = 20,
	Easy = 10,
	Medium = 5,
	Average = 6,
	Hard = 4,
	Impossible = 2,

};
std::vector<std::vector<int>> createBombs(const int w,  const int h, int& bombCount,  int difficulty) {
	std::vector<std::vector<int>> bombGrid;
	std::random_device rd;  
	std::mt19937 eng(rd());  
	std::uniform_int_distribution<> distr(1, 20); 
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (!(distr(eng) % static_cast<int>(difficulty))) {
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
	    std::cout << "Generated Grid (" << w << "x" << h << ")(Bomb Count: " << bombCount << "):\n";
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



void printGrid(const auto& grid, const auto& fGrid, const int& w, const int& h, const bool& hasLost, const int& x, const int& y) {
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
	    if (hasLost) {
		std::string color;
		if(grid[r][c] == -1) {
			if(r == y && c == x) {
			color = "\033[33m";
			} else { 
			color = "\033[36m";
			}
			std::string reset = "\033[0m";
			std::cout << "[" << color << "B" << reset << "] ";
		}
			else {
			std::cout << "[ ] ";
		}
	     
	}
        
    }
std::cout << "\n";
    

}
}






void printGrid(const auto& grid, const auto& fGrid, const int& w, const int& h, const int& STC) {
	std::cout << "Generated Grid (" << w << "x" << h << ")(" << "Safe Tile Count: " << STC << "):\n";
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
		    std::string reset = "\033[0m";
		    std::string color;
		    switch(grid[r][c]) {
			    case 1:
				    color = "\033[32m";
				    break;
			    case 2:
				    color = "\033[92m";
				    break;
			    case 3:
				    color = "\033[93m";
				    break;
			    case 4:
				    color = "\033[94m";
				    break;
			    case 5:
				   color = "\033[95m";
				    break;
			    case 6:
				    color = "\033[96m";
				    break;
			    case 7:
				    color = "\033[91m";
				    break;
			    case 8:
				    color = "\033[97m";				    
				    break;
			   case -1:
				    color = "\033[33m";
				    break;
			    default:
				color = "\033[37m";
				break;




                }
		std::cout << "[" << color << grid[r][c] << reset << "] ";

            } else {
		std::cout << "[ ] ";
	    }
        }
        std::cout << "\n";
    }
    

}


void createGrid (auto& grid, const int& w, const int& h, int& bombCount, int difficulty) {

	auto bombGrid = createBombs(w,h,bombCount, difficulty);
	translateBombs(grid, bombGrid, w, h);

	printGrid(grid, w, h, bombCount);

	



		
	

}

void flagLoc(auto& grid, auto& fGrid, const int& x, const int& y, const int& w, const int& h, const int& STC) {
	 
	if (x >= 0  && x < w && y < h && y >= 0) {
		if(fGrid[y][x] != 1) {
			if(fGrid[y][x] == -2) {
				fGrid[y][x] = 0;
			} else {
				fGrid[y][x] = -2; // -2 because -1 stands for bombed and even though its different maps the distinction will probably save me time, and it can't be a positive number for the same reason
			}
		}

		

	}


	printGrid(grid, fGrid, w, h, STC);

}

void stepLoc (auto& grid, auto& fGrid, const int& x, const int& y, const int& w, const int& h, bool& hasLost, int& STC, bool& firstClick, DIFFICULTY difficulty, int& bombCount) {
	
	if(x >= 0  && x < w && y < h && y >= 0){
		if (hasLost) return;

		if(firstClick) {
		auto bombGrid = createBombs(w, h, bombCount, static_cast<int>(difficulty));
		translateBombs(grid, bombGrid, w, h);
		
		while(grid[y][x] != 0) {
				// Reset grid cells back to 0
				for(int r = 0; r < h; r++) {
					for(int c = 0; c < w; c++) {
						grid[r][c] = 0;
					}
				}
				bombCount = 0;
				bombGrid = createBombs(w, h, bombCount, static_cast<int>(difficulty));
				translateBombs(grid, bombGrid, w, h);
			}

		STC = (w * h) - bombCount;
		firstClick = false;


		}
		
		if(fGrid[y][x] == 0) {
			fGrid[y][x] = 1;

			if (grid[y][x] == -1) {
			
			hasLost = true;
			printGrid(grid, fGrid, w, h, hasLost, x, y);
			
			return;
			
			}
			STC--;
			if (grid[y][x] == 0) {
				std::vector<int> dY = {-1, -1, -1, 0, 0, 1, 1, 1}; // possible Y direction
				std::vector<int> dX = {-1, 0, 1, -1, 1, -1, 0, 1}; // possible X direction
				for (int i = 0; i < 8; i++) {
					int nY = y + dY[i];
					int nX = x + dX[i];
				stepLoc(grid, fGrid, nX, nY, w, h, hasLost, STC, firstClick, difficulty, bombCount);
					

				}
			}
			
			

		}
		
	}
	
	
	
}

void promptUser (auto& grid, auto& fGrid, const int& w, const int& h, bool& hasLost, bool& hasWon, int& STC, DIFFICULTY difficulty, int& bombCount, bool& firstClick) {
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
		flagLoc(grid, fGrid, x, y, w, h, STC);
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
		stepLoc(grid, fGrid, x, y, w, h, hasLost, STC, firstClick, difficulty, bombCount);
	}

}






void setDifficulty (auto& grid, int& w, int& h, int& bombCount, DIFFICULTY& difficulty) {
	bool valueSet = false;
	std::string placeholder;
	while(!valueSet) {
		std::cout << "Set Difficulty, Baby, Easy, Medium, Average, Hard, or IMPOSSIBLE.\n";
		
		
	   std::getline(std::cin, placeholder);
	   if (placeholder == "Baby"){
		   difficulty = DIFFICULTY::Baby;
		   valueSet = true;
	   } else if (placeholder == "Easy") {
		   difficulty = DIFFICULTY::Easy;
		   valueSet = true;
	   } else if (placeholder == "Average") {
		   difficulty = DIFFICULTY::Average;
		   valueSet = true;
	   }
	   else if (placeholder == "Hard") {
		   difficulty = DIFFICULTY::Hard;
		   valueSet = true;
	   }
	   else if (placeholder == "Medium") {
		   difficulty = DIFFICULTY::Medium;
		   valueSet = true;
	   }
	   else if (placeholder == "Impossible" || placeholder == "IMPOSSIBLE") {
		   difficulty = DIFFICULTY::Impossible;
		   valueSet = true;
	   } else {
		   std::cout << "NO TYPOS ALLOWED.\n";
			   }	
	   







	}

	valueSet = false;

	while(!valueSet) {
	std::cout << "CHOSE YOUR WIDTH.\n";
	std::getline(std::cin, placeholder);
	w = std::stoi(placeholder);
	std::cout << "CHOSE YOUR HEIGHT.\n";
	std::getline(std::cin, placeholder);
	h = std::stoi(placeholder);
	valueSet = true;
	}


grid = std::vector<std::vector<int>>(h, std::vector<int>(w, 0));



	}




int main () {
	int bombCount = 0;
	int safeTileCount = 0;
	int h = 20;
	int w = 20;
	bool hasWon = false;
	bool hasLost = false;
	DIFFICULTY difficulty;
	bool FirstClick = true;


	/*
	 * Initialization of the Minesweeper Grid
	 * Firstly, creates bombs via CreateBombs() -> translateBombs() -> createGrid() -> printGrid()
	 * Game Loop via PromptUser either Flagging a point or Stepping (like stepping on a mine) at a point with flash flooding from 0s
	 *
	 *
	 * */

	

	std::vector<std::vector<int>> grid;
	
	setDifficulty(grid, w,h,bombCount, difficulty);
	safeTileCount = (w*h) - bombCount;
	

	std::vector<std::vector<int>> fGrid;
	fGrid = std::vector<std::vector<int>>(h, std::vector<int>(w, 0)); // fGrid stands for flaggedGrid
	while (!(hasWon || hasLost)) {
		promptUser(grid, fGrid, w, h, hasLost, hasWon, safeTileCount, difficulty, bombCount, FirstClick);
		if (!hasLost) {
		printGrid(grid, fGrid, w, h, safeTileCount);
		}
		if(!safeTileCount){
			hasWon = true;
		}


	}


}
