#pragma once
#include "..\OS-ImGui\OS-ImGui_External.h"

namespace Styles
{
    inline void Style_LevelUpLabs()
    {
        // LevelUpLabs style from ImThemes
        ImGuiStyle& style = ImGui::GetStyle();

        style.Alpha = 1.0f;
        style.DisabledAlpha = 0.6000000238418579f;
        style.WindowPadding = ImVec2(6.0f, 3.0f);
        style.WindowRounding = 10.0f;
        style.WindowBorderSize = 1.0f;
        style.WindowMinSize = ImVec2(32.0f, 32.0f);
        style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
        style.WindowMenuButtonPosition = ImGuiDir_Left;
        style.ChildRounding = 10.0f;
        style.ChildBorderSize = 1.0f;
        style.PopupRounding = 5.0f;
        style.PopupBorderSize = 1.0f;
        style.FramePadding = ImVec2(5.0f, 1.0f);
        style.FrameRounding = 5.0f;
        style.FrameBorderSize = 1.0f;
        style.ItemSpacing = ImVec2(8.0f, 4.0f);
        style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
        style.CellPadding = ImVec2(4.0f, 2.0f);
        style.IndentSpacing = 21.0f;
        style.ColumnsMinSpacing = 6.0f;
        style.ScrollbarSize = 13.0f;
        style.ScrollbarRounding = 16.0f;
        style.GrabMinSize = 20.0f;
        style.GrabRounding = 5.0f;
        style.TabRounding = 4.0f;
        style.TabBorderSize = 1.0f;
        style.TabMinWidthForCloseButton = 0.0f;
        style.ColorButtonPosition = ImGuiDir_Right;
        style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
        style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

        style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.08f, 0.94f);
        style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.10f, 0.94f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.63f, 0.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.12f, 0.15f, 1.0f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.15f, 0.18f, 1.0f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.18f, 0.18f, 0.22f, 1.0f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.06f, 0.06f, 0.08f, 1.0f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.08f, 1.0f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.06f, 0.06f, 0.08f, 1.0f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.10f, 0.12f, 1.0f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.06f, 0.06f, 0.08f, 0.5f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.63f, 0.0f, 1.0f, 0.6f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.63f, 0.0f, 1.0f, 0.8f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.63f, 0.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.63f, 0.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.63f, 0.0f, 1.0f, 0.8f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.63f, 0.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.63f, 0.0f, 1.0f, 0.4f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.63f, 0.0f, 1.0f, 0.6f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.63f, 0.0f, 1.0f, 0.8f);
        style.Colors[ImGuiCol_Header] = ImVec4(0.63f, 0.0f, 1.0f, 0.3f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.63f, 0.0f, 1.0f, 0.5f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.63f, 0.0f, 1.0f, 0.7f);
        style.Colors[ImGuiCol_Separator] = ImVec4(0.63f, 0.0f, 1.0f, 0.2f);
        style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.63f, 0.0f, 1.0f, 0.5f);
        style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.63f, 0.0f, 1.0f, 0.8f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.63f, 0.0f, 1.0f, 0.2f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.63f, 0.0f, 1.0f, 0.5f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.63f, 0.0f, 1.0f, 0.8f);
        style.Colors[ImGuiCol_Tab] = ImVec4(0.63f, 0.0f, 1.0f, 0.3f);
        style.Colors[ImGuiCol_TabHovered] = ImVec4(0.63f, 0.0f, 1.0f, 0.6f);
        style.Colors[ImGuiCol_TabActive] = ImVec4(0.63f, 0.0f, 1.0f, 0.8f);
        style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.12f, 0.12f, 0.15f, 1.0f);
        style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.15f, 0.15f, 0.18f, 1.0f);
        style.Colors[ImGuiCol_PlotLines] = ImVec4(0.63f, 0.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.63f, 0.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.12f, 0.12f, 0.15f, 1.0f);
        style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.20f, 0.20f, 0.25f, 1.0f);
        style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.15f, 0.15f, 0.20f, 1.0f);
        style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.63f, 0.0f, 1.0f, 0.35f);
        style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.63f, 0.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.63f, 0.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.70f);
        style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.20f);
        style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.35f);
    }

}
