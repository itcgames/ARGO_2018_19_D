#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Resource {
public:
public:
	Resource();
	virtual ~Resource();

	virtual void loadResource() = 0;
	virtual void unloadResource() = 0;

	void setResourceId(unsigned id) { mResourceId = id; }
	unsigned getResourceId() const { return mResourceId; }

	void setResourcePath(const std::string& path) { mResourcePath = path; }
	std::string getResourcePath() const { return mResourcePath; }

protected:
	unsigned mResourceId;
	std::string mResourcePath;

};
#endif // !RESOURCE_H

