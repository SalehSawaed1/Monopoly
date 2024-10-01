#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "gamemanager.h"
#include "gamehandler.h"
#include "player.h"
#include "propertygrid.h"

namespace py = pybind11;

PYBIND11_MODULE(monopoly_game, m) {
    m.doc() = "Monopoly Game Python Bindings";  // Module docstring

    // Binding for Player class
    py::class_<Player>(m, "Player")
        .def(py::init<const std::string&, int, const QColor&>())  // Constructor
        .def("getName", &Player::getName)
        .def("getBankBalance", &Player::getBankBalance)
        .def("updateBankBalance", &Player::updateBankBalance)
        .def("isInJail", &Player::isInJail)
        .def("setInJail", &Player::setInJail)
        .def("getOwnedProperties", &Player::getOwnedProperties)
        .def("addProperty", &Player::addProperty)
        .def("getJailTurns", &Player::getJailTurns)
        .def("incrementJailTurn", &Player::incrementJailTurn)
        .def("resetJailTurns", &Player::resetJailTurns);

    // Binding for PropertyGrid class
    py::class_<PropertyGrid>(m, "PropertyGrid")
        .def(py::init<QPointF, QPointF, QPointF, QPointF, const std::string&, const std::string&, float, float>())  // Constructor
        .def("getName", &PropertyGrid::getName)
        .def("getPrice", &PropertyGrid::getPrice)
        .def("getRent", &PropertyGrid::getRent)
        .def("getHousePrice", &PropertyGrid::getHousePrice)
        .def("buildHouse", &PropertyGrid::buildHouse)
        .def("buildHotel", &PropertyGrid::buildHotel);

    // Binding for GameHandler class
    py::class_<GameHandler>(m, "GameHandler")
        .def(py::init<GameManager*>())
        .def("handleProperty", &GameHandler::handleProperty)
        .def("handleBuilding", &GameHandler::handleBuilding)
        .def("handleGoToJail", &GameHandler::handleGoToJail)
        .def("handleJail", &GameHandler::handleJail);

    // Binding for GameManager class
    py::class_<GameManager>(m, "GameManager")
        .def(py::init<int, QGraphicsScene*>())
        .def("rollDice", &GameManager::rollDice)
        .def("movePlayer", &GameManager::movePlayer)
        .def("getCurrentPlayer", &GameManager::getCurrentPlayer)
        .def("getPlayers", &GameManager::getPlayers)
        .def("getDiceRoll", &GameManager::getDiceRoll);
}
