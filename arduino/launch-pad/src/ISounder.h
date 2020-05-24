#ifndef ISounder_h
#define ISounder_h

class ISounder
{
public:
	virtual ~ISounder(){};
	virtual void silence() = 0;
	virtual void armed() = 0;
	virtual void passedContinuityTest() = 0;
	virtual void firing() = 0;
};

#endif