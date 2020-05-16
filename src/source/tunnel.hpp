#ifndef TUNEL_H
#define TUNEL_H

#include "constants.hpp"

class tunnel{

public:
    tunnel();
    double in_tunnel(double x, double speed, Direction direction);
    bool is_in_tunnel(double x, Direction direction);
};

#endif // TUNEL_H
