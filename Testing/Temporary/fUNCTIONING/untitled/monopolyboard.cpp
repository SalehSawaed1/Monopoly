#include "monopolyboard.h"
#include "propertygrid.h"
#include "railroadgrid.h"
#include "utilitygrid.h"
#include "surprisegrid.h"
#include "freeparkinggrid.h"
#include "taxgrid.h"
#include "gotojailgrid.h"
#include "jailgrid.h"

MonopolyBoard::MonopolyBoard() {
    initializeBoard();
}

std::vector<Grid*> MonopolyBoard::getBoard() const {
    return m_board;
}


void MonopolyBoard::initializeBoard() {
    // GO grid (Special grid)
    m_board.push_back(new SpecialGrid(PointF(650, 650), PointF(750, 650), PointF(650, 750), PointF(750, 750), "GO"));

    // Property Grids and Special grids
    m_board.push_back(new PropertyGrid(PointF(595, 650), PointF(655, 650), PointF(595, 750), PointF(655, 750), "Mediterranean Avenue", "Brown", 60, 2));

    // Replace "Community Chest" with SurpriseGrid (surprise cards)
    m_board.push_back(new SurpriseGrid(PointF(535, 650), PointF(595, 650), PointF(535, 750), PointF(595, 750), "Community Chest"));

    m_board.push_back(new PropertyGrid(PointF(470, 650), PointF(530, 650), PointF(470, 750), PointF(530, 750), "Baltic Avenue", "Brown", 60, 4));

    // Replace "Income Tax" with TaxGrid
    m_board.push_back(new TaxGrid(PointF(410, 650), PointF(470, 650), PointF(410, 750), PointF(470, 750), "Income Tax", 200));

    m_board.push_back(new RailroadGrid(PointF(350, 650), PointF(410, 650), PointF(350, 750), PointF(410, 750), "Reading Railroad", 200));

    // Continue with other Property, Utility, and Special grids
    m_board.push_back(new PropertyGrid(PointF(290, 650), PointF(350, 650), PointF(290, 750), PointF(350, 750), "Oriental Avenue", "Light Blue", 100, 6));

    // Replace "Chance" with SurpriseGrid
    m_board.push_back(new SurpriseGrid(PointF(225, 650), PointF(290, 650), PointF(225, 750), PointF(290, 750), "Chance"));

    m_board.push_back(new PropertyGrid(PointF(165, 650), PointF(225, 650), PointF(165, 750), PointF(225, 750), "Vermont Avenue", "Light Blue", 100, 6));
    m_board.push_back(new PropertyGrid(PointF(100, 650), PointF(165, 650), PointF(100, 750), PointF(165, 750), "Connecticut Avenue", "Light Blue", 120, 8));

    // Jail Grid
    m_board.push_back(new JailGrid(PointF(3, 650), PointF(100, 650), PointF(3, 750), PointF(100, 750), "Jail"));

    // Continue filling the rest of the board
    m_board.push_back(new PropertyGrid(PointF(3, 590), PointF(103, 590), PointF(3, 650), PointF(103, 650), "St. Charles Place", "Pink", 140, 10));
    m_board.push_back(new UtilityGrid(PointF(3, 530), PointF(103, 530), PointF(3, 590), PointF(103, 590), "Electric Company", 150));
    m_board.push_back(new PropertyGrid(PointF(3, 470), PointF(103, 470), PointF(3, 530), PointF(103, 530), "States Avenue", "Pink", 140, 10));
    m_board.push_back(new PropertyGrid(PointF(3, 410), PointF(103, 410), PointF(3, 470), PointF(103, 470), "Virginia Avenue", "Pink", 160, 12));
    m_board.push_back(new RailroadGrid(PointF(3, 350), PointF(103, 350), PointF(3, 410), PointF(103, 410), "Pennsylvania Railroad", 200));

    // More Property Grids, Utilities, and Railroads
    m_board.push_back(new PropertyGrid(PointF(3, 288), PointF(103, 288), PointF(3, 350), PointF(103, 350), "St. James Place", "Orange", 180, 14));

    // Replace "Community Chest" with SurpriseGrid
    m_board.push_back(new SurpriseGrid(PointF(3, 226), PointF(103, 226), PointF(3, 288), PointF(103, 288), "Community Chest"));

    m_board.push_back(new PropertyGrid(PointF(3, 164), PointF(103, 164), PointF(3, 226), PointF(103, 226), "Tennessee Avenue", "Orange", 180, 14));
    m_board.push_back(new PropertyGrid(PointF(3, 103), PointF(103, 103), PointF(3, 164), PointF(103, 164), "New York Avenue", "Orange", 200, 16));

    // Free Parking Grid
    m_board.push_back(new FreeParkingGrid(PointF(3, 3), PointF(103, 3), PointF(3, 103), PointF(103, 103), "Free Parking"));

    // Continue with the rest of the board (replace Chance and Go To Jail with appropriate grids)
    m_board.push_back(new PropertyGrid(PointF(103, 3), PointF(163, 3), PointF(103, 103), PointF(163, 103), "Kentucky Avenue", "Red", 220, 18));

    // Replace "Chance" with SurpriseGrid
    m_board.push_back(new SurpriseGrid(PointF(163, 3), PointF(224, 3), PointF(163, 103), PointF(224, 103), "Chance"));

    m_board.push_back(new PropertyGrid(PointF(224, 3), PointF(285, 3), PointF(224, 103), PointF(285, 103), "Indiana Avenue", "Red", 220, 18));
    m_board.push_back(new PropertyGrid(PointF(285, 3), PointF(346, 3), PointF(285, 103), PointF(346, 103), "Illinois Avenue", "Red", 240, 20));
    m_board.push_back(new RailroadGrid(PointF(346, 3), PointF(407, 3), PointF(346, 103), PointF(407, 103), "B&O Railroad", 200));

    m_board.push_back(new PropertyGrid(PointF(407, 3), PointF(468, 3), PointF(407, 103), PointF(468, 103), "Atlantic Avenue", "Yellow", 260, 22));
    m_board.push_back(new PropertyGrid(PointF(468, 3), PointF(529, 3), PointF(468, 103), PointF(529, 103), "Ventnor Avenue", "Yellow", 260, 22));
    m_board.push_back(new UtilityGrid(PointF(529, 3), PointF(590, 3), PointF(529, 103), PointF(590, 103), "Water Works", 150));
    m_board.push_back(new PropertyGrid(PointF(590, 3), PointF(652, 3), PointF(590, 103), PointF(652, 103), "Marvin Gardens", "Yellow", 280, 24));

    // Replace "Go To Jail" with GoToJailGrid
    m_board.push_back(new GoToJailGrid(PointF(652, 3), PointF(752, 3), PointF(652, 103), PointF(752, 103), "Go To Jail"));

    m_board.push_back(new PropertyGrid(PointF(652, 103), PointF(752, 103), PointF(652, 163), PointF(752, 163), "Pacific Avenue", "Green", 300, 26));
    m_board.push_back(new PropertyGrid(PointF(652, 163), PointF(752, 163), PointF(652, 224), PointF(752, 224), "North Carolina Avenue", "Green", 300, 26));

    // Replace "Community Chest" with SurpriseGrid
    m_board.push_back(new SurpriseGrid(PointF(652, 224), PointF(752, 224), PointF(652, 285), PointF(752, 285), "Community Chest"));

    m_board.push_back(new PropertyGrid(PointF(652, 285), PointF(752, 285), PointF(652, 346), PointF(752, 346), "Pennsylvania Avenue", "Green", 320, 28));
    m_board.push_back(new RailroadGrid(PointF(652, 346), PointF(752, 346), PointF(652, 407), PointF(752, 407), "Short Line", 200));

    // Replace "Chance" with SurpriseGrid
    m_board.push_back(new SurpriseGrid(PointF(652, 407), PointF(752, 407), PointF(652, 468), PointF(752, 468), "Chance"));

    m_board.push_back(new PropertyGrid(PointF(652, 468), PointF(752, 468), PointF(652, 529), PointF(752, 529), "Park Place", "Blue", 350, 35));

    // Replace "Luxury Tax" with TaxGrid
    m_board.push_back(new TaxGrid(PointF(652, 529), PointF(752, 529), PointF(652, 590), PointF(752, 590), "Luxury Tax", 100));

    m_board.push_back(new PropertyGrid(PointF(652, 590), PointF(752, 590), PointF(652, 652), PointF(752, 652), "Boardwalk", "Blue", 400, 50));
}
