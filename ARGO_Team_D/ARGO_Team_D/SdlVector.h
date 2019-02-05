#ifndef SDLVECTOR_H
#define SDLVECTOR_H

class SdlVector
{
public:
	// Public Functions
	SdlVector();
	SdlVector(float xIn, float yIn);
	~SdlVector();

	// Operators
	//SdlVector operator+(const SdlVector & vec);
	//SdlVector operator-(const SdlVector & vec);
	//SdlVector operator*(const float & val);
	//SdlVector operator/(const float & val);

	// Public Members
	float x;
	float y;
};

#endif // !SDLVECTOR_H

