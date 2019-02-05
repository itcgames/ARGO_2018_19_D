#ifndef COMMAND_H
#define COMMAND_H

#include"ControlSystem.h"
class Command {
public:
	Command(ControlSystem & system);
	virtual ~Command();
	virtual void execute() = 0;
	virtual void undo() = 0;

	virtual bool isExecuted() { return executed; };
protected:
	ControlSystem & m_controlSystem;
	bool executed = false;
};
#endif // !COMMAND_H

