#pragma once
#include"Command.h"
#include<iostream>

class JumpCommand : public Command {
public:
	virtual void execute();
	virtual void undo();
};

class FireCommand : public Command {
public:
	virtual void execute();
	virtual void undo();
};

class CrouchCommand : public Command {
public:
	virtual void execute();
	virtual void undo();
};

class MeleeCommand : public Command {
public:
	virtual void execute();
	virtual void undo();
};

class ShieldCommand : public Command {
public:
	virtual void execute();
	virtual void undo();
};