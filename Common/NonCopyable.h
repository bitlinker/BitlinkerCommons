#pragma once

namespace Commons
{
    class NonCopyable
    {
    protected:
        NonCopyable() {};
    private:
        NonCopyable(const NonCopyable&);
        NonCopyable& operator=(const NonCopyable&);
    };
}