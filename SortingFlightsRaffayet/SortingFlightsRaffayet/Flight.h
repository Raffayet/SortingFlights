#include <string>

class Flight {
public:
    std::string destination;
    std::string departureTime;
    std::string flightNumber;
    std::string gateNumber;

    Flight(const std::string& dest, const std::string& depTime,
        const std::string& fltNumber, const std::string& gNumber)
        : destination(dest), departureTime(depTime),
        flightNumber(fltNumber), gateNumber(gNumber) {}

    bool compare(const Flight& other) const {
        // Пример поређења по времену поласка
        return this->departureTime < other.departureTime;
    }
};