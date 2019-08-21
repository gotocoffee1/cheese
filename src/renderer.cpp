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
                        moveset_fields = cb.get_all_possible_fields(cx, cy);
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

			if (moveset_fields)
            {
                for (size_t i = 0; i < (sizeof(moveset_fields) * 8); i++)
                {
                    if (moveset_fields & (UINT64_C(1) << i))
                    {

                        float px = i % 8;
                        float py = 7 - i / 8;

						ImU32 paint_col = IM_COL32(0, 255, 0, 128);
                        if (chess_board::get_mask((size_t)px, (size_t)(i / 8)) & cb.board[(size_t)color::white] ||
                            chess_board::get_mask((size_t)px, (size_t)(i / 8)) & cb.board[(size_t)color::black])
                            paint_col = IM_COL32(255, 0, 0, 128);

                        px *= square_size;
                        py *= square_size;

                        px += pos.x;
                        py += pos.y;
     
                        draw_list->AddRectFilled({ px, py }, { px + square_size, py + square_size }, paint_col);
                    }
                }
            }
            if (gn::Button("Startposition"))
                cb.start_position();
        }
    }
}
