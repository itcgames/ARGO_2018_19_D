#include "ConcreteCommand.h"

void JumpCommand::execute()
{
	std::cout << "Jump Command" << std::endl;
}

void JumpCommand::undo()
{
	std::cout << "Jump Undone" << std::endl;
}

void FireCommand::execute()
{
	std::cout << "Fire Command" << std::endl;
}

void FireCommand::undo()
{
	std::cout << "Fire Undone" << std::endl;
}

void CrouchCommand::execute()
{
	std::cout << "Crouch Command" << std::endl;
}

void CrouchCommand::undo()
{
	std::cout << "Crouch Undone" << std::endl;
}

void MeleeCommand::execute()
{
	std::cout << "Melee Command" << std::endl;
}

void MeleeCommand::undo()
{
	std::cout << "Melee Undone" << std::endl;
}

void ShieldCommand::execute()
{
	std::cout << "Shield Command" << std::endl;
}

void ShieldCommand::undo()
{
	std::cout << "Shield Undone" << std::endl;
}
