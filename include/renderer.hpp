#pragma once

#include <app.hpp>

namespace cheese
{
    class renderer : public gn::app
    {
    private:
    protected:
        void on_load() override;
        void on_update(bool&) override;
    };
}
