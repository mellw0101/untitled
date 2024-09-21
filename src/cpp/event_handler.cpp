#include "../include/SXL.h"

__SXL_NAMESPACE_BEGIN
event_handler *event_handler::_instance = nullptr;

event_handler *
event_handler::instance(void) noexcept
{
    if (_instance == nullptr)
    {
        _instance = new (std::nothrow) event_handler();
        if (_instance == nullptr)
        {
            logE("Failed to create SXL::event_handler");
            exit(1);
        }
        atexit([] {
            delete _instance;
        });
    }
    return _instance;
}

void
event_handler::handle_event(void) noexcept
{
    while (SDL_PollEvent(&_ev))
    {
        const unsigned int type = utils::event_to_index(_ev.type);
        if (type == (unsigned int)-1 || _map[type].empty())
        {
            continue;
        }
        for (const auto &func : _map[type])
        {
            func(_ev);
        }
    }
}
__SXL_NAMESPACE_END
