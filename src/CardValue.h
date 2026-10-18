#pragma once

class CardValue {
public:

    int value;

    CardValue(int value) {
        this->value = value;
    }

    CardValue() {}

    bool operator>(const CardValue& other) const {
        if (value == 1 && other.value == 13)
            return true;
        return value > other.value;
    }
};