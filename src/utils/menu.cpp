#include "menu.h"

static bool InputTextStdString(const char* label, std::string* str, ImGuiInputTextFlags flags = 0) {
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    return ImGui::InputText(label, str->data(), str->capacity() + 1, flags,
        [](ImGuiInputTextCallbackData* data) -> int {
            if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
                auto str = reinterpret_cast<std::string*>(data->UserData);
                str->resize(data->BufTextLen);
                data->Buf = str->data();
            }
            return 0;
        }, str);
}

void menu::render() {
    if (!globals::menu_open)
        return;

    ImGuiIO& io = GetIO();
    ImGuiStyle& style = GetStyle();

    ImGui::Begin(xorstr("chud"), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

	ImGui::Checkbox(xorstr("Apply Panel Colors"), &globals::override_panel_colors);
    ImGui::SliderInt(xorstr("Panel R"), &globals::panel_r, 0, 255);
    ImGui::SliderInt(xorstr("Panel G"), &globals::panel_g, 0, 255);
    ImGui::SliderInt(xorstr("Panel B"), &globals::panel_b, 0, 255);

	ImGui::Separator();

    ImGui::Checkbox(xorstr("Apply Text Colors"), &globals::override_text_colors);
    ImGui::SliderInt(xorstr("Text R"), &globals::text_r, 0, 255);
    ImGui::SliderInt(xorstr("Text G"), &globals::text_g, 0, 255);
    ImGui::SliderInt(xorstr("Text B"), &globals::text_b, 0, 255);

	ImGui::Separator();

    InputTextStdString(xorstr("Disconnect Message"), &globals::disconnect_msg);
	ImGui::TextWrapped(xorstr("^ Press F4 when in-game to disconnect"));

    ImGui::Separator();

    InputTextStdString(xorstr("Menu background URL"), &globals::menu_bg_url);
    InputTextStdString(xorstr("Loading screen URL"), &globals::load_url);

    if (ImGui::Button(xorstr("Save Config"))) {
        utilities::config_handler(1);
	}

    if (ImGui::Button(xorstr("Load Config"))) {
        utilities::config_handler(2);
    }

    ImGui::End();
}