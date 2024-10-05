#ifndef MONOPOLYBOARD_H
#define MONOPOLYBOARD_H

#include <vector>
#include "Grid.h"
#include "propertygrid.h"
#include "utilitygrid.h"
#include "specialgrid.h"
#include "railroadgrid.h"

class MonopolyBoard {
public:
    MonopolyBoard();

    std::vector<Grid*> getBoard() const;  // Use vector instead of list
    void initializeBoard();

private:
    std::vector<Grid*> m_board;  // Vector of all grids (properties, railroads, utilities, etc.)
};

#endif // MONOPOLYBOARD_H
