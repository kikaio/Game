#pragma once


class DumAct {
protected:
	uint64_t actDelayMsec = 0;
public:
	void setActDelay(int64_t _delayMsec) {
		actDelayMsec = _delayMsec;
	}
public:
	void Do(weak_ptr<DummyUser> _dumWptr) {
		if(auto _dumSptr = _dumWptr.lock()) {
			DoAct(_dumSptr, _dumSptr->GetDummySession());
		}
	}
protected:
	virtual void DoAct(DummyUserSptr _dumSptr, DummySessionSptr _dumSession) = 0;
};


class DumActChat : public DumAct{
public:
	string chatMsg = "dum chat";
protected:
	void DoAct(DummyUserSptr _dumSptr, DummySessionSptr _dumSession) override {
		// todo : dummy user send chat packet using msg value
		JobTimer::Get().Reserve(actDelayMsec, _dumSptr, [_dumSptr, _dumSession, chatMsg=chatMsg]() {
				if (_dumSptr->IsConnected() == false) {
					return;
				}
				UserAndGameServer::ReqChat packet;

				auto* chatInfo = packet.mutable_chat_info();
				auto* profile = chatInfo->mutable_user_profile();
				profile->set_nick_name(_dumSptr->GetNickname());
				chatInfo->set_msg(chatMsg+"from "+ _dumSptr->GetNickname());
				if (_dumSession->SendPacketReqChat(packet) == false) {
					//todo : logging
				}				
				return;
			}
		);
		return ;
	}
};