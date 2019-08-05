#include "renderer.hpp"

#include <stdio.h>

namespace cheese
{
    renderer::renderer(chess_board& cb) : cb(cb)
    {
    }

    void renderer::on_load()
    {
        auto& io = gn::GetIO();
        io.ConfigFlags &= ~ImGuiConfigFlags_ViewportsEnable;
    }

    struct coord
    {
        column x;
        row y;
    };


    void renderer::on_update(bool&)
    {
        if (GN(Window, "Board"))
        {

            ImVec2 pos = gn::GetCursorScreenPos();
            ImDrawList* draw_list = gn::GetWindowDrawList();
            auto p = pos;
            constexpr float square_size = 50.f;

            GN(StyleVar, ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
            uint64_t moveset_fields = 0;

            if (gn::Button("Test"))
                cb.star_positon();

            for (int i = 0; i < 8; ++i)
            {
                for (int j = 0; j < 8; ++j)
                {
                    ImU32 col;
                    column cx = (column)j;
                    row cy = (row)(7 - i);

                    if ((i + j) % 2)
                        col = IM_COL32(124, 75, 64, 255);
                    else
                        col = IM_COL32(228, 193, 151, 255);
                    draw_list->AddRectFilled({ p.x, p.y }, { p.x + square_size, p.y + square_size }, col);
                    auto [fig, color] = cb.get(cb.get_mask(cx, cy));
                    if (fig != figure::none)
                    {
                        auto info = get_info(fig);
                        if (color == color::white)
                            draw_list->AddText(NULL, 24, { p.x, p.y }, IM_COL32(255, 255, 255, 255), info.short_name);
                        else if (color == color::black)
                            draw_list->AddText(NULL, 24, { p.x, p.y }, IM_COL32(0, 0, 0, 255), info.short_name);
                    }
                    gn::Dummy({ square_size, square_size });
                    if (gn::IsItemHovered())
                    {
                        auto source = cb.get_mask(cx, cy);
                        auto [f, c] = cb.get(source);

                        moveset_fields = cb.get_all_possible_fields(cx, cy, f, c);
                    }

                    if (GN(DragDropSource, ImGuiDragDropFlags_SourceAllowNullID))
                    {
                        coord c{ cx, cy };
                        gn::SetDragDropPayload("coord", &c, sizeof(c));
                    }
                    if (GN(DragDropTarget))
                    {
                        if (const ImGuiPayload* payload = gn::AcceptDragDropPayload("coord"))
                        {
                            auto* c = (coord*)payload->Data;
                            cb.move(c->x, c->y, cx, cy);
                        }
                    }
                    gn::SameLine();
                    p.x += square_size;
                }
                gn::NewLine();
                p.x = pos.x;
                p.y += square_size;
            }
            //cout << moveset_fields << "\n";
            draw_list->AddRectFilled({ square_size, square_size }, { 2*square_size, 2*square_size }, IM_COL32(0, 255, 0, 200));
			if (moveset_fields)
            {
                for (size_t i = 0; i <= (sizeof(moveset_fields) * 8); i++)
                {
                    uint64_t lel = 1;
                    if (moveset_fields & (lel << i))
                    {

                        float px = i % 8;
                        float py = 7 - i / 8;
                        //cout << i << " " << px << " " << py << "\n";
                        px *= square_size;
                        py *= square_size;
                        
                        draw_list->AddRectFilled({ px, py }, { px + square_size, py + square_size }, IM_COL32(0, 255, 0, 128));
                    }
                }
            }
        }
    }
}
