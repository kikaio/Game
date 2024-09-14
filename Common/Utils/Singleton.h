#pragma once

template<typename T>
class Singleton
{
public:
	static T& Get() {
		static T inst;
		return inst;
	}
};