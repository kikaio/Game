#pragma once 

template<typename T>
class TLSSingleton {
public:
	static T& Get() {
		static thread_local T inst;
		return inst;
	}
};