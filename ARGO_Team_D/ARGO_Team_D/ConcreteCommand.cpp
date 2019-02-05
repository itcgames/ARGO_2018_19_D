#include "ConcreteCommand.h"

JumpCommand::JumpCommand(ControlSystem & system): Command(system)
{
}

void JumpCommand::execute()
{
	//std::cout << "Jump Command" << std::endl;
	//executed = true;
}

void JumpCommand::undo()
{
	std::cout << "Jump Undone" << std::endl;
}

FireCommand::FireCommand(ControlSystem & system): Command(system)
{
}

void FireCommand::execute()
{
	//std::cout << "Fire Command" << std::endl;
	//executed = true;
	m_controlSystem.fire();
}

void FireCommand::undo()
{
	std::cout << "Fire Undone" << std::endl;
}

MoveCommand::MoveCommand(ControlSystem & system) : Command(system)
{
}

void MoveCommand::execute()
{
	//std::cout << "Move Command" << std::endl;
	//executed = true;
	m_controlSystem.move();
}

void MoveCommand::undo()
{
	std::cout << "Move Undone" << std::endl;
}

MeleeCommand::MeleeCommand(ControlSystem & system) : Command(system)
{
}

void MeleeCommand::execute()
{
	//std::cout << "Melee Command" << std::endl;
	//executed = true;
}

void MeleeCommand::undo()
{
	std::cout << "Melee Undone" << std::endl;
}

SwitchWeaponCommand::SwitchWeaponCommand(ControlSystem & system) : Command(system)
{
}

void SwitchWeaponCommand::execute()
{
	//std::cout << "Switch Weapon Command" << std::endl;
	//executed = true;
}

void SwitchWeaponCommand::undo()
{
	std::cout << "Switch Weapon Undone" << std::endl;
}
