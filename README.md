# Monopoly Game

## Overview
This project is a digital version of the classic board game **Monopoly**, implemented in **C++** using the **Qt framework**. The game supports **2 to 8 players** who play on the same computer, following standard Monopoly rules with additional enhanced dynamic features like property management, rent payments, and player movement on the board.

## Features
- **Multiplayer Gameplay**: Supports 2 to 8 players on the same computer.
- **Dynamic Board**: The board contains 40 spaces, including properties, railroads, utilities, tax spaces, special spaces like "Go to Jail" and "Free Parking", and surprise spaces with dynamic events.
- **Property Management**: Players can buy properties, build houses, and upgrade to hotels. Rent is calculated based on property ownership and development level.
- **Surprise Cards**: Players draw dynamic surprise cards that may move them to specific spaces, reward them, or send them to jail.
- **Jail Mechanic**: Players may end up in jail if they roll doubles three times consecutively or land on the "Go to Jail" space. They can use a card, pay a fine, or roll doubles to get out.
- **Winning Conditions**: Players win if all others go bankrupt or if they accumulate a balance of 4000 currency units.

## Project Structure
The project is organized into multiple classes and files, each handling specific aspects of the game:

### Key Classes and Files
- **`GameManager`**: Manages the overall game flow, dice rolls, player turns, and win conditions.
- **`GameHandler`**: Handles interactions and logic for different board spaces like properties, railroads, and utilities.
- **`Player`**: Manages player information such as balance, properties owned, and player status (e.g., in jail or bankrupt).
- **`PropertyGrid`, `RailroadGrid`, `UtilityGrid`**: Classes representing the various types of spaces on the board.
- **`SurpriseGrid`**: Defines spaces where players draw surprise cards.
- **`form.ui`**: The GUI layout designed using Qt's UI designer.
- **`form.cpp`**: Contains the logic for the UI and connects the visual elements with the game mechanics.

## Monopoly Board Setup
The board consists of 40 spaces with the following setup:

### Properties
- **Mediterranean Avenue** (Brown): $60, Rent: $2
- **Baltic Avenue** (Brown): $60, Rent: $4
- **Oriental Avenue** (Light Blue): $100, Rent: $6
- **Vermont Avenue** (Light Blue): $100, Rent: $6
- **Connecticut Avenue** (Light Blue): $120, Rent: $8
- **St. Charles Place** (Pink): $140, Rent: $10
- **States Avenue** (Pink): $140, Rent: $10
- **Virginia Avenue** (Pink): $160, Rent: $12
- **St. James Place** (Orange): $180, Rent: $14
- **Tennessee Avenue** (Orange): $180, Rent: $14
- **New York Avenue** (Orange): $200, Rent: $16
- **Kentucky Avenue** (Red): $220, Rent: $18
- **Indiana Avenue** (Red): $220, Rent: $18
- **Illinois Avenue** (Red): $240, Rent: $20
- **Atlantic Avenue** (Yellow): $260, Rent: $22
- **Ventnor Avenue** (Yellow): $260, Rent: $22
- **Marvin Gardens** (Yellow): $280, Rent: $24
- **Pacific Avenue** (Green): $300, Rent: $26
- **North Carolina Avenue** (Green): $300, Rent: $26
- **Pennsylvania Avenue** (Green): $320, Rent: $28
- **Park Place** (Blue): $350, Rent: $35
- **Boardwalk** (Blue): $400, Rent: $50

### Railroads
- **Reading Railroad**: $200
- **Pennsylvania Railroad**: $200
- **B&O Railroad**: $200
- **Short Line**: $200

### Utilities
- **Electric Company**: $150
- **Water Works**: $150

### Special Spaces
- **GO**: Collect $200 when passing.
- **Jail**: Players are sent here based on certain events.
- **Free Parking**: No action, players rest here.
- **Go To Jail**: Players are sent directly to jail.
- **Income Tax**: Players pay $200.
- **Luxury Tax**: Players pay $100.
- **Surprise Grids**: Dynamic spaces that draw cards for various events like moving to another space, receiving money, or going to jail.

## How to Run the Project
### Prerequisites
- **Qt Framework**: Install Qt (version 5.15 or higher) and Qt Creator.
- **C++ Compiler**: Ensure a C++ compiler (like `g++`) is set up on your machine.
- **Git** (optional): For cloning the project.

### Setup Instructions
1. **Clone the Project Repository**:
   ```bash
   git clone <repository-url>
   cd Monopoly-Game

