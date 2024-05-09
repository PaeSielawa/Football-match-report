// Coded by PS
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

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
    std::pair<StatystykiDruzyny, StatystykiDruzyny> stats;

public:
    Mecz() {}

    void goalScored(std::string teamName) {
        if (teamName == "host") {
            stats.first.addGoal();
        }
        else if (teamName == "guest") {
            stats.second.addGoal();
        }
    }

    void redCard(std::string teamName) {
        if (teamName == "host") {
            stats.first.addRedCard();
        }
        else if (teamName == "guest") {
            stats.second.addRedCard();
        }
    }

    void yellowCard(std::string teamName) {
        if (teamName == "host") {
            stats.first.addYellowCard();
        }
        else if (teamName == "guest") {
            stats.second.addYellowCard();
        }
    }

    void foul(std::string teamName) {
        if (teamName == "host") {
            stats.first.addFoul();
        }
        else if (teamName == "guest") {
            stats.second.addFoul();
        }
    }

    void shotOnTarget(std::string teamName) {
        if (teamName == "host") {
            stats.first.addShotOnTarget();
        }
        else if (teamName == "guest") {
            stats.second.addShotOnTarget();
        }
    }

    void shotOffTarget(std::string teamName) {
        if (teamName == "host") {
            stats.first.addShotOffTarget();
        }
        else if (teamName == "guest") {
            stats.second.addShotOffTarget();
        }
    }

    StatystykiDruzyny getStats(std::string teamName) const {
        if (teamName == "host") {
            return stats.first;
        }
        else if (teamName == "guest") {
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
    std::vector<std::tuple<int, std::string, std::string>> zdarzenia;

public:
    Redaktor(std::string username, std::string password)
        : User(username, password, "admin") {}

    void addGoalEvent(Zawodnik& zawodnik, Mecz& match, std::string teamName, int minute) {
        Event event;
        event.goal(zawodnik, match, teamName);
        zdarzenia.push_back(std::make_tuple(minute, teamName, "Gol"));
    }

    void addRedCardEvent(Zawodnik& zawodnik, Mecz& match, std::string teamName, int minute) {
        Event event;
        event.redCard(zawodnik, match, teamName);
        zdarzenia.push_back(std::make_tuple(minute, teamName, "Czerwona kartka"));
    }

    void addYellowCardEvent(Zawodnik& zawodnik, Mecz& match, std::string teamName, int minute) {
        Event event;
        event.yellowCard(zawodnik, match, teamName);
        zdarzenia.push_back(std::make_tuple(minute, teamName, "Zolta kartka"));
    }

    void addFoulEvent(Mecz& match, std::string teamName, int minute) {
        Event event;
        event.foul(match, teamName);
        zdarzenia.push_back(std::make_tuple(minute, teamName, "Faul"));
    }

    void addShotOnTargetEvent(Mecz& match, std::string teamName, int minute) {
        Event event;
        event.shotOnTarget(match, teamName);
        zdarzenia.push_back(std::make_tuple(minute, teamName, "Strzal celny"));
    }

    void addShotOffTargetEvent(Mecz& match, std::string teamName, int minute) {
        Event event;
        event.shotOffTarget(match, teamName);
        zdarzenia.push_back(std::make_tuple(minute, teamName, "Strzal niecelny"));
    }

    std::vector<std::tuple<int, std::string, std::string>> getEvents() const {
        return zdarzenia;
    }
};

class Czytelnik : public User {

public:
    Czytelnik(std::string username, std::string password)
        : User(username, password, "czytelnik") {}

    void wyswietlStatystykiMeczu(Mecz& match) {
        auto statsA = match.getStats("host");
        auto statsB = match.getStats("guest");

        std::cout << "Calkowite statystyki meczu:\n" << std::endl;
        std::cout << "\t\t\tTeam A\t\t\tTeam B" << std::endl;
        std::cout << "----------------------------------------------------------------" << std::endl;
        std::cout << "Gole:\t\t\t" << statsA.getGoals() << "\t\t\t" << statsB.getGoals() << std::endl;
        std::cout << "Czerwone kartki:\t" << statsA.getRedCards() << "\t\t\t" << statsB.getRedCards() << std::endl;
        std::cout << "Zolte kartki:\t\t" << statsA.getYellowCards() << "\t\t\t" << statsB.getYellowCards() << std::endl;
        std::cout << "Faule:\t\t\t" << statsA.getFouls() << "\t\t\t" << statsB.getFouls() << std::endl;
        std::cout << "Strzaly celne:\t\t" << statsA.getShotsOnTarget() << "\t\t\t" << statsB.getShotsOnTarget() << std::endl;
        std::cout << "Strzaly niecelne:\t" << statsA.getShotsOffTarget() << "\t\t\t" << statsB.getShotsOffTarget() << std::endl;
    }

    void wyswietlPosortowaneZdarzenia(Redaktor& redaktor) {
        std::vector<std::tuple<int, std::string, std::string>> zdarzenia = redaktor.getEvents();
        std::sort(zdarzenia.begin(), zdarzenia.end(),
            [](const std::tuple<int, std::string, std::string>& a, const std::tuple<int, std::string, std::string>& b) {
                return std::get<0>(a) < std::get<0>(b);
            });

        std::cout << "\nPosortowane zdarzenia meczu:" << std::endl;
        std::cout << "Minuta\t\tDruzyna\t\tEvent" << std::endl;
        for (const auto& zdarzenie : zdarzenia) {
            int minute;
            std::string teamName, eventType;
            std::tie(minute, teamName, eventType) = zdarzenie;
            std::cout << minute << "\t\t" << teamName << "\t\t" << eventType << std::endl;
        }
    }
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
    Druzyna teamA(teamAPlayers, "host");
    Druzyna teamB(teamBPlayers, "guest");

    // Tworzenie meczu
    Mecz match;

    // Tworzenie redaktora
    Redaktor redaktor("admin", "admin");

    // Zdarzenia dla drużyny A
    redaktor.addGoalEvent(player1, match, "host", 10);
    redaktor.addRedCardEvent(player2, match, "host", 20);
    redaktor.addShotOnTargetEvent(match, "host", 30);
    redaktor.addShotOffTargetEvent(match, "host", 40);
    redaktor.addGoalEvent(player1, match, "host", 90);

    // Zdarzenia dla drużyny B
    redaktor.addGoalEvent(player3, match, "guest", 15);
    redaktor.addRedCardEvent(player4, match, "guest", 25);
    redaktor.addShotOnTargetEvent(match, "guest", 35);
    redaktor.addShotOffTargetEvent(match, "guest", 45);

    // Wyświetlanie całkowitych statystyk meczu
    Czytelnik czytelnik("reader", "pass");
    czytelnik.wyswietlStatystykiMeczu(match);
    czytelnik.wyswietlPosortowaneZdarzenia(redaktor);

    return 0;
}
