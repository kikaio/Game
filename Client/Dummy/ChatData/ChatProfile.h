#pragma once

class ChatProfile {
private:
	int64_t profileId = 0;
	string nickName = "";
	int64_t profileHeroId = 0;
	int64_t profileFrameId = 0;
public:
	void SetProfileId(int64_t _id);
	void SetNickName(const string& _name);
	void SetProfileHeroId(int64_t _id);
	void SetProfileFrameId(int64_t _id);
public:
	int64_t GetProfileId() const ;
	const string& GetNickName() const ;
	int64_t GetProfileHeroId() const ;
	int64_t GetProfileFrameId() const ;
public:
	void Render();
};