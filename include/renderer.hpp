#pragma once

#include <app.hpp>
#include "chess_board.hpp"

namespace cheese
{
    class renderer : public gn::app
    {
    private:
        chess_board& cb;
    protected:
        void on_load() override;
        void on_update(bool&) override;
    public:
        renderer(chess_board&);
    };
}
