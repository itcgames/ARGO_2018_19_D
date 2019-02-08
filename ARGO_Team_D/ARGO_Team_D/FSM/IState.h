#ifndef ISTATE_H
#define ISTATE_H

class IState {
public:
	IState() {}
	virtual ~IState() {};

	//State change functions
	virtual void onEntry() = 0;
	virtual void onExit() = 0;
};

#endif //!ISTATE_H