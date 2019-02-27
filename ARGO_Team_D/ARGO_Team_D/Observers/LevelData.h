#ifndef LEVELDATA_H
#define LEVELDATA_H

#include "Subject.h"
#include <vector>

class LevelData : public Subject {
public:
	LevelData(int killLimit);

	void registerObserver(Observer *observer) override;

	void removeObserver(Observer *observer) override;

	void notifyObservers() override;

	void enemyKilled();

	void reset(int killLimit);

	int getKillLimit();

	int getEnemiesKilled();

private:
	std::vector<Observer *> observers; // observers

	int m_killLimit = 0;
	int m_enemiesKilled = 0;
};
#endif