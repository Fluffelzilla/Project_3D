 #ifndef _CLOCK_H
#define _CLOCK_H
#include<chrono>

namespace EngineUtils
{
	class TimeHandler
	{
	private:
		static TimeHandler* myInstance;
		std::chrono::system_clock::time_point myStartTime;
		std::chrono::duration<float> myDeltaTime;
		float myTimeScale;

		TimeHandler();
		~TimeHandler();
	public:
		static TimeHandler* instance();
		static void release();
		void reset();
		float deltaTime();
		void timeScale(float t = 1.0f);
		float timeScale();
		void tick();
	};
}


#endif // !_CLOCK_H