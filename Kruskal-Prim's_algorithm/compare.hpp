#pragma once
#include "edge.hpp"

struct Compare{
    bool operator()(Edge const & e1, Edge const & e2)
    {
        return !(e1.weight < e2.weight);
    }
};
