#include "pch.h"
#include "DBManager.h"

DBManager::DBManager()
	: driver(get_driver_instance())
{
}

DBManager::~DBManager()
{
	Clear();
}

void DBManager::Clear()
{
}

