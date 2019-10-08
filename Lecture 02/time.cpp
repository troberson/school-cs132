#include <iostream>

class Time {
    private:
    int hour, min;

    public:
    void print() {
        std::cout << hour << ":" << min;
    }

    void setHour(int hr) {
        hour = 0;
        if (hr >= 0 && hr <= 23) {
            hour = hr;
        }
    }

    void setMin(int minute) {
        min = 0;
        if (minute >= 0 && minute <= 59) {
            min = minute;
        }
    }
};

int main() {
    Time t, t2;

    t.setHour(12);
    t.setMin(67);
    t.print();
    std::cout << std::endl;

    t2.print();
    std::cout << "\n\n";
}