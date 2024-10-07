#pragma once

class UserSession : public Session
{
public:
	~UserSession();
protected:
	//virtual void AfterSended(UInt32 _bytes) {
	//	printf("send bytes : %d\n", _bytes);
	//}
};