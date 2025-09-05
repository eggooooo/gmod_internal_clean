void __fastcall hooks::handles::html_panel_load_url(void* html_panel, const char* url) {
    if (!strstr(url, xorstr("asset://garrysmod/html/menu.html")))
        url = globals::load_url.c_str();

    originals::html_panel_load_url(html_panel, url);
}