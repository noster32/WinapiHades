#pragma once
#include "GLAPI.h"

class EngineAPI
{
private:
	bool shutdown;

public:
	static EngineAPI& GetInstance() {
		static EngineAPI instance;
		return instance;
	}

	void StopEngine() { shutdown = true; }

	bool InternalGetShutdown() { return shutdown; }

private:
	EngineAPI() : shutdown(false) { }

};