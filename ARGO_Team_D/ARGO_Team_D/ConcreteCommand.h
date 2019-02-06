#include"Command.h"
#include<iostream>
#include"ControlSystem.h"

#ifndef JUMPCOMMAND_H
#define JUMPCOMMAND_H
class JumpCommand : public Command {
public:
	JumpCommand(ControlSystem & system);
	virtual void execute();
	virtual void undo();
};
#endif // !JUMPCOMMAND_H


#ifndef FIRECOMMAND_H
#define FIRECOMMAND_H
class FireCommand : public Command {
public:
	FireCommand(ControlSystem & system);
	virtual void execute();
	virtual void undo();
};
#endif // !FIRECOMMAND_H


#ifndef MOVERIGHTCOMMAND_H
#define MOVERIGHTCOMMAND_H
class MoveRightCommand : public Command {
public:
	MoveRightCommand(ControlSystem & system);
	virtual void execute();
	virtual void undo();
};
#endif // !MOVERIGHTCOMMAND_H

#ifndef MOVELEFTCOMMAND_H
#define MOVELEFTCOMMAND_H
class MoveLeftCommand : public Command {
public:
	MoveLeftCommand(ControlSystem & system);
	virtual void execute();
	virtual void undo();
};
#endif // !MOVELEFTCOMMAND_H


#ifndef MELEECOMMAND_H
#define MELEECOMMAND_H
class MeleeCommand : public Command {
public:
	MeleeCommand(ControlSystem & system);
	virtual void execute();
	virtual void undo();
};
#endif // !MELEECOMMAND_H


#ifndef SWITCHWEAPONCOMMAND_H
#define SWITCHWEAPONCOMMAND_H
class SwitchWeaponCommand : public Command {
public:
	SwitchWeaponCommand(ControlSystem & system);
	virtual void execute();
	virtual void undo();
};
#endif // !SWITCHWEAPONCOMMAND_H

