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

	void handleEvent(const Event& theEvent) override;

private:
	bool mIsInit;

};

