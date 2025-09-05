int __fastcall hooks::handles::html_panel_paint(void* html_panel) {
    globals::menu_panel = html_panel;

    static std::once_flag once;
    std::call_once(once, [html_panel]() {
        const char* setup_script = R"(
        function UpdateBackground(url) { 
        $('body').css({ 
        'background-image': scope.InGame ? 'none' : 'url("' + url + '")', 
        'background-size': scope.InGame ? 'auto' : '100% 100%', 
        'background-repeat': scope.InGame ? 'repeat' : 'no-repeat' 
        });  
        }
        setInterval(function(){ UpdateBackground(currentUrl); }, 1000);
        )";

        utilities::run_javascript(html_panel, setup_script);
    });

    std::string update_call = "currentUrl = \"" + std::string(globals::menu_bg_url) + "\"; UpdateBackground(currentUrl);";
    utilities::run_javascript(html_panel, update_call.c_str());

    return originals::html_panel_paint(html_panel);
}