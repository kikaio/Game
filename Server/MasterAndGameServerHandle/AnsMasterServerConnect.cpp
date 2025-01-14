#include "pch.h"
#include "ServerTypes.h"
#include "MasterAndGameServerHandle.h"

namespace MasterAndGameServerHandle {
	bool AnsMasterServerConnect(MasterSessionSptr _session, MasterAndGameServer::AnsMasterServerConnect& _packet)
	{
		printf("AnsMasterServerConnect\n");
		return true;
	}
}