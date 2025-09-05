#include "hooks/hooks.h"
#include "utils/color.h"

DWORD WINAPI initialize(HMODULE base) {
    while (!utilities::game_is_fully_loaded())
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

#ifdef _DEBUG
    utilities::attach_console();
#endif

    interfaces::initialize();
    hooks::initialize();
    utilities::config_handler(2);

    return TRUE;
}

BOOL WINAPI shutdown() {
#ifdef _DEBUG
    utilities::detach_console();
#endif
    hooks::shutdown();
    return TRUE;
}

BOOL WINAPI DllMain(HMODULE base, DWORD ul_reason_for_call, LPVOID reserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(base);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)initialize, base, 0, nullptr);
        return TRUE;
    case DLL_PROCESS_DETACH:
        if (reserved == nullptr)
            return shutdown();
        return TRUE;
    default:
        return TRUE;
    }
}