#include "genogrove/Key.hpp"

namespace genogrove {
    /**
     * @details The default constructor create an empty Key object
     */
    Key::Key() : interval(std::string::npos, std::string::npos), strand('\0'), data(nullptr),
        singleLink(nullptr),  multiLink(std::vector<Key*>()) {}
    Key::Key(Interval intvl) : interval(intvl), strand('\0'), data(nullptr),
        singleLink(nullptr),  multiLink(std::vector<Key*>()) {}
    Key::~Key() {}

    // operators opverloading
    bool Key::operator<(const Key& other) const { return this->interval < other.interval; }
    bool Key::operator>(const Key& other) const { return this->interval > other.interval; }

    // getter & setter
    Interval Key::getInterval() { return this->interval; }
    void Key::setInterval(Interval interval) { this->interval = interval; }
    char Key::getStrand() { return this->strand; }
    void Key::setStrand(char strand) { this->strand = strand; }
    std::shared_ptr<AnyBase> Key::getData() { return this->data; }
    void Key::setData(std::shared_ptr<AnyBase> data) {this->data = data;}
    Key* Key::getSingleLink() { return this->singleLink; }
    void Key::setSingleLink(Key* singleLink) { this->singleLink = singleLink; }
    std::vector<Key*> Key::getMultiLink() { return this->multiLink; }
    void Key::setMultiLink(std::vector<Key*> multiLink) { this->multiLink = multiLink; }

    // serialize
    void Key::serialize(std::ostream& os) const {
//        std::cout << "\t\tserialize key" << std::endl;
        interval.serialize(os);

        bool hasData = (data != nullptr); // check if there is data
        os.write(reinterpret_cast<const char*>(&hasData), sizeof(hasData));

        if(hasData) {
            std::string typeName = data->getTypeName();
            size_t typeNameLength = typeName.size();
            os.write(reinterpret_cast<const char*>(&typeNameLength), sizeof(typeNameLength));
            os.write(typeName.c_str(), typeNameLength);

            data->serialize(os);

            bool hasSingleLink = (singleLink != nullptr);
            os.write(reinterpret_cast<const char*>(&hasSingleLink), sizeof(hasSingleLink));
            if(hasSingleLink) {
                singleLink->serialize(os);
            }

            size_t multiLinkSize = multiLink.size();
            os.write(reinterpret_cast<const char*>(&multiLinkSize), sizeof(multiLinkSize));
            for(auto& link : multiLink) {
                link->serialize(os);
            }
        }
    }

    Key Key::deserialize(std::istream& is) {
        Interval interval = Interval::deserialize(is);
//        std::cout << "\tkey boundaries: " << interval.getStart() << "," << interval.getEnd() << std::endl;
        Key key(interval);

        bool hasData;
        is.read(reinterpret_cast<char*>(&hasData), sizeof(hasData));

        if(hasData) {
//            std::cout << "\t\t\tdeserialize data" << std::endl;
            size_t typeNameLength;
            is.read(reinterpret_cast<char*>(&typeNameLength), sizeof(typeNameLength));
            std::string typeName(typeNameLength, '\0');
            is.read(&typeName[0], typeNameLength);

            // deserialize the data
            key.data = TypeRegistry::create(typeName);
            key.data->deserialize(is);

            bool hasSingleLink;
            is.read(reinterpret_cast<char*>(&hasSingleLink), sizeof(hasSingleLink));
            if(hasSingleLink) {
                key.singleLink = new Key(Key::deserialize(is));
            }

            size_t multiLinkSize;
            is.read(reinterpret_cast<char*>(&multiLinkSize), sizeof(multiLinkSize));
            key.multiLink.resize(multiLinkSize);
            for(size_t i=0; i < multiLinkSize; ++i) {
                key.multiLink[i] = new Key(Key::deserialize(is));
            }
        } else {

        }
        return key;
    }
}

