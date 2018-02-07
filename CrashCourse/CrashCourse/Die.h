#pragma once

class Die {
public:
    Die();
    Die(unsigned int sides);
    ~Die();

    unsigned int numSides() const { return mSides; }
    void setSides(unsigned int sides);
    unsigned int roll() const;

private:
    static const unsigned int MIN_SIDES;

    void validateSides() const;

    unsigned int mSides;
};

