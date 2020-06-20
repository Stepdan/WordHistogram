#pragma once

#include <functional>
#include <memory>

#include "Proc/Interfaces/IHistogram.h"

namespace Proc
{

class ProcessManager
{
public:
    using DataCallbackType = std::function<void(Items&&)>;
    using ProgressCallbackType = std::function<void(size_t, bool)>;

    struct Initializer
    {
        DataCallbackType dataCallback;
        ProgressCallbackType progressCallback;
    };

public:
    ProcessManager(Initializer&&);
    ~ProcessManager();

public:
    void SetOpenPath(const QString&);

    void Start();
    void Stop();

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

}
