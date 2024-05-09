#include <iostream>
#include <string>
#include <vector>

class Zawodnik {
    std::string firstName;
    std::string surname;
    std::string number;
    std::string team;
    int goals = 0;
    int assists = 0;
    int yellowCards = 0;
    int redCards = 0;

public:
    Zawodnik(std::string firstName, std::string surname, std::string number, std::string team)
        : firstName(firstName), surname(surname), number(number), team(team) {}

    void addGoal() { goals++; }
    void addAssist() { assists++; }
    void addYellowCard() { yellowCards++; }
    void addRedCard() { redCards++; }

    std::string getFirstName() const { return firstName; }
    std::string getSurname() const { return surname; }
    int getGoals() const { return goals; }
    int getAssists() const { return assists; }
    int getYellowCards() const { return yellowCards; }
    int getRedCards() const { return redCards; }
};

class Druzyna {
    std::vector<Zawodnik> listaZawodnikow;
    std::string name;
    int balance = 0;
    int wins = 0;
    int loses = 0;
    int draws = 0;

public:
    Druzyna(std::vector<Zawodnik> listaZawodnikow, std::string name)
        : listaZawodnikow(listaZawodnikow), name(name) {}

    void goalScored() { balance++; }
    void goalLost() { balance--; }
    std::string getName() const { return name; }
};

class StatystykiDruzyny {
    int goals;
    int redCards;
    int yellowCards;
    int fouls;
    int shotsOnTarget;
    int shotsOffTarget;

public:
    StatystykiDruzyny()
        : goals(0), redCards(0), yellowCards(0), fouls(0), shotsOnTarget(0), shotsOffTarget(0) {}

    void addGoal() { goals++; }
    void addRedCard() { redCards++; }
    void addYellowCard() { yellowCards++; }
    void addFoul() { fouls++; }
    void addShotOnTarget() { shotsOnTarget++; }
    void addShotOffTarget() { shotsOffTarget++; }

    int getGoals() const { return goals; }
    int getRedCards() const { return redCards; }
    int getYellowCards() const { return yellowCards; }
    int getFouls() const { return fouls; }
    int getShotsOnTarget() const { return shotsOnTarget; }
    int getShotsOffTarget() const { return shotsOffTarget; }
};

class Mecz {
    std::pair<StatystykiDruzyny, StatystykiDruzyny> stats; // Para przechowująca statystyki dla obu drużyn

public:
    Mecz() {}

    void goalScored(std::string teamName) {
        if (teamName == "gospodarz") {
            stats.first.addGoal();
        }
        else if (teamName == "gosc") {
            stats.second.addGoal();
        }
    }

    void redCard(std::string teamName) {
        if (teamName == "gospodarz") {
            stats.first.addRedCard();
        }
        else if (teamName == "gosc") {
            stats.second.addRedCard();
        }
    }

    void yellowCard(std::string teamName) {
        if (teamName == "gospodarz") {
            stats.first.addYellowCard();
        }
        else if (teamName == "gosc") {
            stats.second.addYellowCard();
        }
    }

    void foul(std::string teamName) {
        if (teamName == "gospodarz") {
            stats.first.addFoul();
        }
        else if (teamName == "gosc") {
            stats.second.addFoul();
        }
    }

    void shotOnTarget(std::string teamName) {
        if (teamName == "gospodarz") {
            stats.first.addShotOnTarget();
        }
        else if (teamName == "gosc") {
            stats.second.addShotOnTarget();
        }
    }

    void shotOffTarget(std::string teamName) {
        if (teamName == "gospodarz") {
            stats.first.addShotOffTarget();
        }
        else if (teamName == "gosc") {
            stats.second.addShotOffTarget();
        }
    }

    StatystykiDruzyny getStats(std::string teamName) const {
        if (teamName == "gospodarz") {
            return stats.first;
        }
        else if (teamName == "gosc") {
            return stats.second;
        }
    }
};

class Event {
public:
    Event() {}

    void goal(Zawodnik& zawodnik, Mecz& match, std::string teamName) {
        zawodnik.addGoal();
        match.goalScored(teamName);
    }

    void redCard(Zawodnik& zawodnik, Mecz& match, std::string teamName) {
        zawodnik.addRedCard();
        match.redCard(teamName);
    }

    void yellowCard(Zawodnik& zawodnik, Mecz& match, std::string teamName) {
        zawodnik.addYellowCard();
        match.yellowCard(teamName);
    }

    void foul(Mecz& match, std::string teamName) {
        match.foul(teamName);
    }

    void shotOnTarget(Mecz& match, std::string teamName) {
        match.shotOnTarget(teamName);
    }

    void shotOffTarget(Mecz& match, std::string teamName) {
        match.shotOffTarget(teamName);
    }
};

class User {
    std::string username;
    std::string password;
    std::string permission;

public:
    User(const std::string& username, const std::string& password, const std::string& permission)
        : username(username), password(password), permission(permission) {}

    std::string getUsername() const {
        return username;
    }

    std::string getPassword() const {
        return password;
    }

    std::string getPermission() const {
        return permission;
    }

    void setPassword(const std::string& newPassword) {
        password = newPassword;
    }
};

class Redaktor : public User {

public:
    Redaktor(std::string username, std::string password)
        : User(username, password, "admin") {}

    void addGoalEvent(Zawodnik& zawodnik, Mecz& match, std::string teamName) {
        Event event;
        event.goal(zawodnik, match, teamName);
    }

    void addRedCardEvent(Zawodnik& zawodnik, Mecz& match, std::string teamName) {
        Event event;
        event.redCard(zawodnik, match, teamName);
    }

    void addYellowCardEvent(Zawodnik& zawodnik, Mecz& match, std::string teamName) {
        Event event;
        event.yellowCard(zawodnik, match, teamName);
    }

    void addFoulEvent(Mecz& match, std::string teamName) {
        Event event;
        event.foul(match, teamName);
    }

    void addShotOnTargetEvent(Mecz& match, std::string teamName) {
        Event event;
        event.shotOnTarget(match, teamName);
    }

    void addShotOffTargetEvent(Mecz& match, std::string teamName) {
        Event event;
        event.shotOffTarget(match, teamName);
    }
};

class Czytelnik : public User {

public:
    Czytelnik(std::string username, std::string password)
        : User(username, password, "czytelnik") {}
};

int main() {
    // Tworzenie zawodników
    Zawodnik player1("John", "Doe", "10", "Team A");
    Zawodnik player2("Jane", "Smith", "7", "Team A");
    Zawodnik player3("Michael", "Johnson", "9", "Team B");
    Zawodnik player4("Emily", "Brown", "5", "Team B");

    // Tworzenie drużyn
    std::vector<Zawodnik> teamAPlayers = { player1, player2 };
    std::vector<Zawodnik> teamBPlayers = { player3, player4 };
    Druzyna teamA(teamAPlayers, "gospodarz");
    Druzyna teamB(teamBPlayers, "gosc");

    // Tworzenie meczu
    Mecz match;

    // Tworzenie redaktora
    Redaktor redaktor("admin", "admin");

    // Zdarzenia dla drużyny A
    redaktor.addGoalEvent(player1, match, "gospodarz");
    redaktor.addRedCardEvent(player2, match, "gospodarz");
    redaktor.addShotOnTargetEvent(match, "gospodarz");
    redaktor.addShotOffTargetEvent(match, "gospodarz");

    // Zdarzenia dla drużyny B
    redaktor.addGoalEvent(player3, match, "gosc");
    redaktor.addRedCardEvent(player4, match, "gosc");
    redaktor.addShotOnTargetEvent(match, "gosc");
    redaktor.addShotOffTargetEvent(match, "gosc");

    // Wyświetlanie całkowitych statystyk meczu
    auto statsA = match.getStats("gospodarz");
    auto statsB = match.getStats("gosc");

    std::cout << "Calkowite statystyki meczu:\n" << std::endl;
    std::cout << "\t\t\tTeam A\t\t\tTeam B" << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;
    std::cout << "Gole:\t\t\t" << statsA.getGoals() << "\t\t\t" << statsB.getGoals() << std::endl;
    std::cout << "Czerwone kartki:\t" << statsA.getRedCards() << "\t\t\t" << statsB.getRedCards() << std::endl;
    std::cout << "Zolte kartki:\t\t" << statsA.getYellowCards() << "\t\t\t" << statsB.getYellowCards() << std::endl;
    std::cout << "Faule:\t\t\t" << statsA.getFouls() << "\t\t\t" << statsB.getFouls() << std::endl;
    std::cout << "Strzaly celne:\t\t" << statsA.getShotsOnTarget() << "\t\t\t" << statsB.getShotsOnTarget() << std::endl;
    std::cout << "Strzaly niecelne:\t" << statsA.getShotsOffTarget() << "\t\t\t" << statsB.getShotsOffTarget() << std::endl;

    return 0;
}
