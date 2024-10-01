#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // For handling standard library types like std::vector
#include "player.h"
#include "propertygrid.h"
#include "utilitygrid.h"
#include "railroadgrid.h"
#include "surprisegrid.h"
#include "taxgrid.h"
#include "gotojailgrid.h"
#include "freeparkinggrid.h"
#include "monopolyboard.h"
#include "specialgrid.h"

namespace py = pybind11;

PYBIND11_MODULE(monopoly_game_bindings, m) {
    // Binding Player class
    py::class_<Player>(m, "Player")
        .def(py::init<const QString&, int, QColor>())
        .def("getName", &Player::getName)
        .def("getColor", &Player::getColor)
        .def("getBankBalance", &Player::getBankBalance)
        .def("updateBankBalance", &Player::updateBankBalance)
        .def("getCurrentGrid", &Player::getCurrentGrid)
        .def("setCurrentGrid", &Player::setCurrentGrid)
        .def("getOwnedProperties", &Player::getOwnedProperties)
        .def("getNumHouses", &Player::getNumHouses)
        .def("getNumHotels", &Player::getNumHotels)
        .def("getOutOfJailCards", &Player::getOutOfJailCards)
        .def("addProperty", &Player::addProperty);

    // Binding PropertyGrid class
    py::class_<PropertyGrid, Grid>(m, "PropertyGrid")
        .def(py::init<QPointF, QPointF, QPointF, QPointF, const QString&, const QString&, float, float>())
        .def("getName", &PropertyGrid::getName)
        .def("getPrice", &PropertyGrid::getPrice)
        .def("getRent", &PropertyGrid::getRent)
        .def("getHousePrice", &PropertyGrid::getHousePrice)
        .def("getHotelPrice", &PropertyGrid::getHotelPrice)
        .def("getNumHouses", &PropertyGrid::getNumHouses)
        .def("hasHotel", &PropertyGrid::hasHotel);

    // Binding UtilityGrid class
    py::class_<UtilityGrid, Grid>(m, "UtilityGrid")
        .def(py::init<QPointF, QPointF, QPointF, QPointF, const QString&, int>())
        .def("getName", &UtilityGrid::getName)
        .def("getPrice", &UtilityGrid::getPrice);

    // Binding RailroadGrid class
    py::class_<RailroadGrid, Grid>(m, "RailroadGrid")
        .def(py::init<QPointF, QPointF, QPointF, QPointF, const QString&, float>())
        .def("getName", &RailroadGrid::getName)
        .def("getPrice", &RailroadGrid::getPrice);

    // Binding SurpriseGrid class
    py::class_<SurpriseGrid, SpecialGrid>(m, "SurpriseGrid")
        .def(py::init<QPointF, QPointF, QPointF, QPointF, const QString&>());

    // Binding TaxGrid class
    py::class_<TaxGrid, SpecialGrid>(m, "TaxGrid")
        .def(py::init<QPointF, QPointF, QPointF, QPointF, const QString&, int>());

    // Binding GoToJailGrid class
    py::class_<GoToJailGrid, SpecialGrid>(m, "GoToJailGrid")
        .def(py::init<QPointF, QPointF, QPointF, QPointF, const QString&>());

    // Binding FreeParkingGrid class
    py::class_<FreeParkingGrid, SpecialGrid>(m, "FreeParkingGrid")
        .def(py::init<QPointF, QPointF, QPointF, QPointF, const QString&>());

    // Binding MonopolyBoard class
    py::class_<MonopolyBoard>(m, "MonopolyBoard")
        .def(py::init<>())
        .def("getBoard", &MonopolyBoard::getBoard);

    // Binding SpecialGrid class
    py::class_<SpecialGrid, Grid>(m, "SpecialGrid")
        .def(py::init<QPointF, QPointF, QPointF, QPointF, const QString&>())
        .def("getName", &SpecialGrid::getName);

    // Binding Grid base class
    py::class_<Grid>(m, "Grid")
        .def("getTopLeft", &Grid::getTopLeft)
        .def("getTopRight", &Grid::getTopRight)
        .def("getBottomLeft", &Grid::getBottomLeft)
        .def("getBottomRight", &Grid::getBottomRight)
        .def("calculateRandomPoint", &Grid::calculateRandomPoint)
        .def("getName", &Grid::getName);  // Virtual function to be overridden by derived classes
}
