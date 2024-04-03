#pragma once

namespace Lava
{
    struct LAVA_API LightSourceComponent
    {
        enum class Kind
        {
            Parallel,
            Point,
            Spot
        };
        Kind Which;

        LightSourceComponent(Kind kind): Which(kind) { }
    };
}
