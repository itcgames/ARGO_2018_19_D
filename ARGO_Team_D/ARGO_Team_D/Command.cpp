#include "Command.h"
Command::Command(ControlSystem & system) :
	m_controlSystem{ system }
{
}

Command::~Command()
{
}

bool Command::isExecuted() 
{ 
	return m_executed; 
}
