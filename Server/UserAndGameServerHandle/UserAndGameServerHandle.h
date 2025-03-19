#pragma once

namespace UserAndGameServerHandle {
	bool ReqChat(UserSessionSptr _session, UserAndGameServer::ReqChat& _packet);
	bool ReqLogin(UserSessionSptr _session, UserAndGameServer::ReqLogin& _packet);
	bool ReqGameConn(UserSessionSptr _session, UserAndGameServer::ReqGameConn& _packet);
}