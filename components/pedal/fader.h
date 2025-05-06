#ifndef FADER_H
#define FADER_H

#include <vector>
#include <string>

class Fader{
    public:
    std::string title;

    Fader(const std::string& title, int value=0);

    void setValue(int value);
    int getValue() const;
    void up();
    void down();
    void select();
    void unselect();
    void toggleSelect();
    bool isSelected() const;
    void addValue(int value);

    private:
    int value{0};
    int minValue{0};
    int maxValue{100};
    bool selected{false};
};

#endif // FADER_H