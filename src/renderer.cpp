#include "renderer.hpp"

#include <stdio.h>

namespace cheese
{
    void renderer::on_update(bool&)
    {
        if (GN(Window, "Board"))
        {

			if (gn::Button("Test"))
                printf("fuck off");
            ImVec2 pos = gn::GetCursorScreenPos();
            ImDrawList* draw_list = gn::GetWindowDrawList();
            auto p = pos;
            for (int i = 0; i < 8; ++i)
            {
                for (int j = 0; j < 8; ++j)
                {
                    ImU32 col;

                    if ((i + j) % 2)
                        col = IM_COL32(124, 75, 64, 255);
                    else
                        col = IM_COL32(228, 193, 151, 255);
                    draw_list->AddRectFilled({ p.x, p.y }, { p.x + 50, p.y + 50 }, col);
                    p.x += 50;
                }
                p.x = pos.x;
                p.y += 50;
            }
        }
    }
}