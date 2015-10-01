#pragma once

namespace Commons
{
    class NonObject
    {
    private:
        NonObject() {};
        NonObject(const NonObject&);
        NonObject& operator=(const NonObject&);
    };
}
