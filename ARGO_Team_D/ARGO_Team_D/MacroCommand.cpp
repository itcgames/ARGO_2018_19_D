#include "MacroCommand.h"

MacroCommand::MacroCommand()
{
	commands = new std::list<Command*>();
}

MacroCommand::~MacroCommand()
{
}

void MacroCommand::add(Command * c)
{
	commands->push_back(c);
}

void MacroCommand::remove(Command * c)
{
	commands->remove(c);
}

void MacroCommand::removeAll()
{
	commands->clear();
}

void MacroCommand::execute()
{
	std::list<Command *>::iterator it = commands->begin();
	std::list<Command *>::iterator end = commands->end();

	for (; it != end; it++)
	{
		(*it)->execute();
	}
}

void MacroCommand::undo()
{
	auto it = commands->rbegin();
	auto end = commands->rend();

	for (; it != end; it++)
	{
		(*it)->undo();
	}
}

std::list<Command*>* MacroCommand::getCommands()
{
	return commands;
}
