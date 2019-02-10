#ifndef COMMAND_H
#define COMMAND_H

#include"ControlSystem.h"
class Command {
public:
	Command(ControlSystem & system);
	virtual ~Command();
	virtual void execute() = 0;
	virtual bool isExecuted();

protected:
	ControlSystem & m_controlSystem;
	bool m_executed = false;
};
#endif // !COMMAND_H

