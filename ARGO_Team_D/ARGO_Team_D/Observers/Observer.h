#ifndef OBSERVER_H
#define OBSERVER_H

/// <summary>
/// Observer Interface class.
/// </summary>
class Observer {
public:
	/**
	* Update the observer.
	*/
	virtual void update(bool complete) = 0;
};
#endif
