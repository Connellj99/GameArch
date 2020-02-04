#pragma once
#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include "EventListener.h"

class InputTranslator : public EventListener
{
public:
	InputTranslator();
	~InputTranslator();

	void init();
	void cleanup();

	

private:
	void handleEvent(const Event& theEvent) override;
	bool mIsInit;

};

