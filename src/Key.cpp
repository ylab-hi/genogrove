#include "Key.hpp"

Key::Key() : interval({std::string::npos, std::string::npos}),
    data(nullptr), singleLink(nullptr),  multiLink(std::vector<Key*>()) {}
Key::~Key() {}

// operators opverloading
bool Key::operator<(const Key& other) const {
    return this->interval.first < other.interval.first;
}
//bool Key::operator>(const Key& other) const {
//    return this->interval.first > other.interval.first;
//}
//
//// getter & setter
//dtp::Interval Key::getInterval() { return this->interval; }
//void Key::setInterval(dtp::Interval interval) { this->interval = interval; }
//std::shared_ptr<void> Key::getData() { return this->data; }
//void Key::setData(std::shared_ptr<void> data) { this->data = data; }
//Key* Key::getSingleLink() { return this->singleLink; }
//void Key::setSingleLink(Key* singleLink) { this->singleLink = singleLink; }
//std::vector<Key*> Key::getMultiLink() { return this->multiLink; }
//void Key::setMultiLink(std::vector<Key*> multiLink) { this->multiLink = multiLink; }
//
