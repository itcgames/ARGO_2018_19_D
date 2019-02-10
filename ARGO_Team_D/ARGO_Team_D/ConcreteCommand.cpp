#include "ConcreteCommand.h"

// Jump
JumpCommand::JumpCommand(ControlSystem & system): Command(system)
{
}

void JumpCommand::execute()
{
	m_controlSystem.jump();
}

// Fire
FireCommand::FireCommand(ControlSystem & system): Command(system)
{
}

void FireCommand::execute()
{
	m_controlSystem.fire();
}

// Move Left
MoveLeftCommand::MoveLeftCommand(ControlSystem & system) : Command(system)
{
}

void MoveLeftCommand::execute()
{
	m_controlSystem.moveLeft();
}

// Move Right
MoveRightCommand::MoveRightCommand(ControlSystem & system) : Command(system)
{
}

void MoveRightCommand::execute()
{
	m_controlSystem.moveRight();
}

// Melee
MeleeCommand::MeleeCommand(ControlSystem & system) : Command(system)
{
}

void MeleeCommand::execute()
{
}


// Switch Weapon
SwitchWeaponCommand::SwitchWeaponCommand(ControlSystem & system) : Command(system)
{
}

void SwitchWeaponCommand::execute()
{
}
