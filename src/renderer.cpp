#include "renderer.hpp"

#include <stdio.h>

namespace cheese
{
    void renderer::on_load()
    {
        auto& io = gn::GetIO();
        io.ConfigFlags &= ~ImGuiConfigFlags_ViewportsEnable;
    }

    void renderer::on_update(bool&)
    {
        if (GN(Window, "Board"))
        {

            ImVec2 pos = gn::GetCursorScreenPos();
            ImDrawList* draw_list = gn::GetWindowDrawList();
            auto p = pos;
            constexpr float square_size = 50.f;

            for (int i = 0; i < 8; ++i)
            {
                for (int j = 0; j < 8; ++j)
                {
                    ImU32 col;

                    if ((i + j) % 2)
                        col = IM_COL32(124, 75, 64, 255);
                    else
                        col = IM_COL32(228, 193, 151, 255);
                    draw_list->AddRectFilled({ p.x, p.y }, { p.x + square_size, p.y + square_size }, col);
                    gn::Dummy({ square_size, square_size });
                    if (gn::IsItemClicked())
                        printf("pos x:%d y:%d\n", j, i);
                    gn::SameLine();
                    p.x += square_size;
                }
                gn::NewLine();
                p.x = pos.x;
                p.y += square_size;
            }
        }
    }
}
