# Football Match Statistics System

A C++ application for managing and displaying football match statistics. The system allows recording various match events and viewing match statistics in real-time.

## Features

- **Match Event Recording**
  - Goals
  - Red/Yellow cards
  - Fouls
  - Shots (on/off target)
  - Player statistics tracking

- **User Roles**
  - Editor (`Redaktor`) - can add match events
  - Reader (`Czytelnik`) - can view match statistics

- **Statistics Display**
  - Total match statistics for both teams
  - Chronologically sorted match events
  - Team-specific statistics

## Class Structure

### Core Classes
- `Zawodnik` - Player class with personal info and statistics
- `Druzyna` - Team class managing players and team statistics
- `Mecz` - Match class handling game events and statistics
- `StatystykiDruzyny` - Team statistics container

### User Management
- `User` - Base user class
- `Redaktor` - Editor role with event management capabilities
- `Czytelnik` - Reader role with statistics viewing capabilities

## Usage Example

```cpp
// Create players
Zawodnik player1("John", "Doe", "10", "Team A");
Zawodnik player2("Jane", "Smith", "7", "Team A");

// Create teams
std::vector<Zawodnik> teamAPlayers = { player1, player2 };
Druzyna teamA(teamAPlayers, "host");

// Create match
Mecz match;

// Create editor and add events
Redaktor redaktor("admin", "admin");
redaktor.addGoalEvent(player1, match, "host", 10);
redaktor.addShotOnTargetEvent(match, "host", 30);

// View statistics
Czytelnik czytelnik("reader", "pass");
czytelnik.wyswietlStatystykiMeczu(match);
czytelnik.wyswietlPosortowaneZdarzenia(redaktor);
```

## Building the Project

This project uses Visual Studio 2022 and C++17. To build:

1. Open `main.sln` in Visual Studio
2. Select the desired configuration (Debug/Release)
3. Build the solution (F7)

## Requirements

- Visual Studio 2022
- C++17 or later
- Windows platform

## License

This project was created by PS. All rights reserved.
