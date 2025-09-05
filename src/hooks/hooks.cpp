#include "hooks.h"
#include "handles/wndproc.h"
#include "handles/d3d9/present.h"
#include "handles/d3d9/reset.h"
#include "handles/html_panel/load_url.h"
#include "handles/html_panel/paint.h"
#include "handles/net_channel/send_datagram.h"
#include "handles/panel/paint_traverse.h"
#include "handles/surface/set_draw_color.h"
#include "handles/surface/set_text_color.h"

void hooks::initialize() {
    if (!min_hook.create_hook((LPVOID)memory::get_virtual((PVOID**)interfaces::panel, 41), &handles::paint_traverse, (LPVOID*)&handles::originals::paint_traverse))
        throw;

    if (!min_hook.create_hook((LPVOID)memory::get_virtual((PVOID**)interfaces::surface, 15), &handles::set_draw_color, (LPVOID*)&handles::originals::set_draw_color))
        throw;

    if (!min_hook.create_hook((LPVOID)memory::get_virtual((PVOID**)interfaces::surface, 23), &handles::set_text_color, (LPVOID*)&handles::originals::set_text_color))
        throw;

    if (!min_hook.create_hook((LPVOID)memory::pattern_scanner(xorstr("gameoverlayrenderer64.dll"), xorstr("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 81 EC ? ? ? ? 4C 8B A4 24 ? ? ? ?")), &handles::present, (LPVOID*)&handles::originals::present))
        throw;

    if (!min_hook.create_hook((LPVOID)memory::pattern_scanner(xorstr("gameoverlayrenderer64.dll"), xorstr("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 50 48 8B F2 48 8B F9 48 8B D1")), &handles::reset, (LPVOID*)&handles::originals::reset))
        throw;

    if (!min_hook.create_hook((LPVOID)memory::relative_to_absolute((uintptr_t)memory::pattern_scanner(xorstr("menusystem.dll"), xorstr("E8 ? ? ? ? EB 17 48 8B 0D ? ? ? ?")), 1, 5), &handles::html_panel_load_url, (LPVOID*)&handles::originals::html_panel_load_url))
        throw;

    if (!min_hook.create_hook((LPVOID)memory::pattern_scanner(xorstr("menusystem.dll"), xorstr("40 57 48 83 EC 40 48 8B F9")), &handles::html_panel_paint, (LPVOID*)&handles::originals::html_panel_paint))
        throw;

    if (!min_hook.create_hook((LPVOID)memory::pattern_scanner(xorstr("engine.dll"), xorstr("40 55 53 56 57 41 55 41 56 41 57 48 8D AC 24 E0")), &handles::send_datagram, (LPVOID*)&handles::originals::send_datagram))
        throw;

    if (!min_hook.enable_hook())
        throw;

    handles::originals::wndproc = (WNDPROC)SetWindowLongPtrW(interfaces::window, GWLP_WNDPROC, (LONG_PTR)handles::wndproc);
}

void hooks::shutdown() {
    min_hook.remove_all_hooks();
    SetWindowLongPtrW(interfaces::window, GWLP_WNDPROC, (LONG_PTR)handles::originals::wndproc);
}
