#include "genogrove/Key.hpp"

namespace genogrove {
    /**
     * @details The default constructor create an empty Key object
     */
    Key::Key() : interval(std::string::npos, std::string::npos), data(nullptr),
        singleLink(nullptr),  multiLink(std::vector<Key*>()) {}
    Key::Key(Interval intvl) : interval(intvl), data(nullptr),
        singleLink(nullptr),  multiLink(std::vector<Key*>()) {}
    Key::~Key() {}

    // operators opverloading
    bool Key::operator<(const Key& other) const { return this->interval < other.interval; }
    bool Key::operator>(const Key& other) const { return this->interval > other.interval; }

    // getter & setter
    Interval Key::getInterval() { return this->interval; }
    void Key::setInterval(Interval interval) { this->interval = interval; }
    std::shared_ptr<AnyBase> Key::getData() { return this->data; }
    void Key::setData(std::shared_ptr<AnyBase> data) {this->data = data;}
    Key* Key::getSingleLink() { return this->singleLink; }
    void Key::setSingleLink(Key* singleLink) { this->singleLink = singleLink; }
    std::vector<Key*> Key::getMultiLink() { return this->multiLink; }
    void Key::setMultiLink(std::vector<Key*> multiLink) { this->multiLink = multiLink; }

}

