#ifndef CONCRETECOMMAND_H
#define CONCRETECOMMAND_H

#include "Command.h"
#include <iostream>
#include "ControlSystem.h"

// Jump Command
class JumpCommand : public Command {
public:
	JumpCommand(ControlSystem & system);
	virtual void execute();
};

// Fire Command
class FireCommand : public Command {
public:
	FireCommand(ControlSystem & system);
	virtual void execute();
};

// Move Left Command
class MoveLeftCommand : public Command {
public:
	MoveLeftCommand(ControlSystem & system);
	virtual void execute();
};

// Move Right Command
class MoveRightCommand : public Command {
public:
	MoveRightCommand(ControlSystem & system);
	virtual void execute();
};

// Melee Command
class MeleeCommand : public Command {
public:
	MeleeCommand(ControlSystem & system);
	virtual void execute();
};

// Switch Weapon Command
class SwitchWeaponCommand : public Command {
public:
	SwitchWeaponCommand(ControlSystem & system);
	virtual void execute();
};

#endif // !CONCRETECOMMAND_H
