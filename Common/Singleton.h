#pragma once

namespace Commons
{
    template<class T>
    class Singleton
    {
	public:
        static T& getInstance()
        {
            static T mInstance;
            return mInstance;
        }
        
    protected:
		Singleton() {};
	private:
		Singleton(const Singleton&);
		Singleton& operator=(const Singleton&);
    };
}
