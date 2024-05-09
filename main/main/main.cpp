#include <iostream>
#include <vector>
#include <string>
#include <utility>

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
};

class Redaktor : public User {

public:
	Redaktor(std::string username, std::string password)
		: User(username, password, "admin") {}


};

class Czytelnik : public User {

public:
	Czytelnik(std::string username, std::string password)
		: User(username, password, "czytelnik") {}
};

class Zawodnik {
	std::string firstName;
	std::string surname;
	std::string number;
	std::string team;
	int goals;
	int assists;
	int yellowCards;
	int redCards;
public:
	Zawodnik(std::string firstName, std::string surname, std::string number, std::string team, int goals, int assists, int yellowCards, int redCards)
		: firstName(firstName), surname(surname), number(number), team(team), goals(goals), yellowCards(yellowCards), redCards(redCards) {}

	void addGoal() { goals++; }
	void addAssist() { assists++; }
	void addYellowCard() { yellowCards++; }
	void addRedCards() { redCards++; }
	std::string getFirstName() const { return firstName; }
	std::string getSurname() const { return surname; }
	int getGoals() const { return goals; }
};

class Druzyna {
	std::vector<Zawodnik> listaZawodnikow;
	std::string name;
	int balance;
	int wins;
	int loses;
	int draws;
public:
	Druzyna(std::vector<Zawodnik> listaZawodnikow, std::string name, int balance, int wins, int loses, int draws) 
		: listaZawodnikow(listaZawodnikow), name(name), balance(balance), wins(wins), loses(loses), draws(draws) {}

	void goalScored() { balance++; }
	void goalLost() { balance--; }
	std::string getName() const { return name; }
};

class Mecz {
	std::pair<int, int> result;
	int numOfCards;
	int numOfCorners;
	int numOfFouls;
public:
	Mecz() : result(std::make_pair(0, 0)), numOfCards(0), numOfCorners(0), numOfFouls(0) {}

	void changeResult(int goalsTeam1, int goalsTeam2) {
		result.first += goalsTeam1; // Dodajemy liczbę goli zdobytych przez pierwszą drużynę
		result.second += goalsTeam2; // Dodajemy liczbę goli zdobytych przez drugą drużynę
	}

	void addCard() { numOfCards++; }
	void addCorner() { numOfCorners++; }
	void addFoul() { numOfFouls++; }

	std::pair<int, int> getResult() const { return result; }
	int getNumOfCards() const { return numOfCards; }
	int getNumOfCorners() const { return numOfCorners; }
	int getNumOfFouls() const { return numOfFouls; }

};

class Event {
	std::string name;
public:
	Event(std::string name) : name(name) {}

	void goal(Zawodnik& zawodnik,Druzyna& team, Mecz& match) {
		zawodnik.addGoal();
		match.changeResult(1, 0);
		team.goalScored();
	}

	void card(Zawodnik& zawodnik, Mecz& match) {
		zawodnik.addYellowCard();
		match.addCard();
	}

	void corner(Druzyna& team, Mecz& match) {
		match.addCorner();
	}

	void foul(Zawodnik& zawodnik, Mecz& match) {
		match.addFoul();
	}
};

int main()
{
	// Tworzenie zawodników
	Zawodnik player1("John", "Doe", "10", "Team A", 0, 0, 0, 0);
	Zawodnik player2("Jane", "Smith", "7", "Team A", 0, 0, 0, 0);

	// Tworzenie drużyn
	std::vector<Zawodnik> teamAPlayers = { player1, player2 };
	Druzyna teamA(teamAPlayers, "Team A", 0, 0, 0, 0);

	// Tworzenie meczu
	Mecz match;

	// Tworzenie zdarzenia (strzelenie gola przez zawodnika)
	Event event("Goal");
	event.goal(player1, teamA, match);

	// Wyświetlanie wyniku meczu
	auto result = match.getResult();
	std::cout << "Wynik meczu: " << teamA.getName() << " vs " << "Team B" << std::endl;
	std::cout << teamA.getName() << ": " << result.first << std::endl;
	std::cout << "Team B: " << result.second << std::endl;

	// Wyświetlanie statystyk zawodników
	std::cout << "Statystyki zawodnika " << player1.getFirstName() << " " << player1.getSurname() << ":" << std::endl;
	std::cout << "Liczba goli: " << player1.getGoals() << std::endl;

	return 0;
}

