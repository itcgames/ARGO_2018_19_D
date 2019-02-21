#include "LevelData.h"

LevelData::LevelData(int killLimit)
{
	m_killLimit = killLimit;
}

void LevelData::registerObserver(Observer * observer)
{
	observers.push_back(observer);
}

void LevelData::removeObserver(Observer * observer)
{
	// find the observer
	auto iterator = std::find(observers.begin(), observers.end(), observer);

	if (iterator != observers.end()) { // observer found
		observers.erase(iterator); // remove the observer
	}
}

void LevelData::notifyObservers()
{
	for (Observer *observer : observers) { // notify all observers
		observer->update(true);
	}
}

void LevelData::enemyKilled()
{
	m_enemiesKilled += 1;

	if (m_enemiesKilled >= m_killLimit) {
		notifyObservers();
	}
}