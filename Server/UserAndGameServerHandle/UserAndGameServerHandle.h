#pragma once

namespace UserAndGameServerHandle {
	bool ReqLogin(UserSessionSptr _session, UserAndGameServer::ReqLogin& _packet);
	bool ReqGameConn(UserSessionSptr _session, UserAndGameServer::ReqGameConn& _packet);
}