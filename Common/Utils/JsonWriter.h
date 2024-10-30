#pragma once

using namespace rapidjson;

class JsonWriter : public JsonParser
{
public:
	JsonWriter() {}
	~JsonWriter() {}
private:
	Document doc;
};