#pragma once

class Board {

public:
    Board() {}
    virtual ~Board() {}

    virtual Board* clone() = 0;
};