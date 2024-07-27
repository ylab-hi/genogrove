#include "Key.hpp"

Key::Key(dtp::Interval intvl) : interval(intvl),
    data(nullptr), singleLink(nullptr),  multiLink(std::vector<Key*>()) {}

Key::Key(dtp::Interval intvl, std::shared_ptr<void> data) : interval(intvl),
    data(data), singleLink(nullptr),  multiLink(std::vector<Key*>()) {}


Key::~Key() {}

// operators opverloading
bool Key::operator<(const Key& other) const {
    if(this->interval.first < other.interval.first &&
        this->interval.first < other.interval.second) {
        return true;
    } else {
        return false;
    }
}
bool Key::operator>(const Key& other) const {
    if(this->interval.first > other.interval.first &&
        this->interval.first > other.interval.second) {
        return true;
    } else {
        return false;
    }
}

// getter & setter
dtp::Interval Key::getInterval() { return this->interval; }
void Key::setInterval(dtp::Interval interval) { this->interval = interval; }
std::shared_ptr<void> Key::getData() { return this->data; }
void Key::setData(std::shared_ptr<void> data) { this->data = data; }
Key* Key::getSingleLink() { return this->singleLink; }
void Key::setSingleLink(Key* singleLink) { this->singleLink = singleLink; }
std::vector<Key*> Key::getMultiLink() { return this->multiLink; }
void Key::setMultiLink(std::vector<Key*> multiLink) { this->multiLink = multiLink; }
