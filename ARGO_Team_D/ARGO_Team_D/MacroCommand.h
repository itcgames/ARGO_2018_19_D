#pragma once
#include"Command.h"
#include<vector>
#include<list>
class MacroCommand: public Command {
public:
	MacroCommand();
	virtual ~MacroCommand();
	virtual void add(Command * c);
	virtual void remove(Command * c);
	virtual void removeAll();
	virtual void execute();
	virtual void undo();
	std::list<Command *> * getCommands();
private:
	std::list<Command *>* commands;
};