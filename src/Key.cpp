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

    // serialize
    void Key::serialize(std::ostream& os) const {
        interval.serialize(os);
        if(data) {
            bool hasData = false;
            os.write(reinterpret_cast<const char*>(&hasData), sizeof(hasData));

            // get the type name
            std::string typeName = data->getDataTypeIndex().name();
            size_t typeNameLength = typeName.size();
            os.write(reinterpret_cast<const char*>(&typeNameLength), sizeof(typeNameLength));
            os.write(typeName.c_str(), typeNameLength);

            data->serialize(os);
        } else {
            bool hasData = false;
            os.write(reinterpret_cast<const char*>(&hasData), sizeof(hasData));
        }
    }

    Key Key::deserialize(std::istream& is) {
        Key key = Key::deserialize(is);

        // deserialize the data
        size_t typeNameLength;
        is.read(reinterpret_cast<char*>(&typeNameLength), sizeof(typeNameLength));
        std::string typeName(typeNameLength, '\0');
        is.read(&typeName[0], typeNameLength);

        std::shared_ptr<AnyBase> data = data->deserialize(is);



        return key;
    }

}

