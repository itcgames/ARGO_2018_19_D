#ifndef LEVELOBSERVER_H
#define LEVELOBSERVER_H

#include "Observer.h"

class LevelObserver : public Observer {
	int m_id;
	bool m_levelComplete = false;

public:

	LevelObserver(int id) { m_id = id; }

	virtual void update(bool complete) override;

	bool getComplete() { return m_levelComplete; }

};

#endif