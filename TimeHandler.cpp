#include "TimeHandler.h"
namespace EngineUtils
{
	TimeHandler* TimeHandler::myInstance = nullptr;

	TimeHandler* TimeHandler::instance()
	{
		if (myInstance == nullptr)
		{
			myInstance = new TimeHandler();

		}
		return myInstance;
	}

	void TimeHandler::release()
	{
		delete myInstance;
		myInstance = nullptr;
	}

	TimeHandler::TimeHandler()
	{
		reset();
		myTimeScale = 1.0f;
		myDeltaTime = std::chrono::duration<float>(0.0f);
	}

	TimeHandler::~TimeHandler()
	{

	}

	void TimeHandler::reset()
	{
		myStartTime = std::chrono::system_clock::now();
	}

	float TimeHandler::deltaTime()
	{
		return myDeltaTime.count();
	}

	void TimeHandler::timeScale(float t /*=1.0f*/)
	{
		myTimeScale = t;
	}

	float TimeHandler::timeScale()
	{
		return myTimeScale;
	}

	void TimeHandler::tick()
	{
		myDeltaTime = std::chrono::system_clock::now() - myStartTime;
	}
}

