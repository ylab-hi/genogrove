#ifndef IBPTREE_KEY_HPP
#define IBPTREE_KEY_HPP

// Standard
#include <memory>
#include <vector>
#include <typeindex>
#include <optional>
#include <any>

// Class
#include "DataTypes.hpp"
#include "Interval.hpp"
#include "TypeRegistry.hpp"
#include "AnyType.hpp"

namespace genogrove {
    class Interval; // forward declaration

    class Key {
    public:
        Key();
        Key(Interval interval);
        template<typename T>
        Key(Interval intvl, T&& data) :
            interval(intvl),
            data(std::make_shared<AnyType<std::decay_t<T>>>(data)),
            singleLink(nullptr),
            multiLink(std::vector<Key*>()) {
                // register the type of the data with the TypeRegistry
                genogrove::TypeRegistry::registerType<T>();
            }
        ~Key();

        bool operator<(const Key& other) const;
        bool operator>(const Key& other) const;

        // getter & setter
        Interval getInterval();
        void setInterval(Interval interval);
        std::shared_ptr<AnyBase> getData();
        void setData(std::shared_ptr<AnyBase> data);
        Key* getSingleLink();
        void setSingleLink(Key* singleLink);
        std::vector<Key*> getMultiLink();
        void setMultiLink(std::vector<Key*> multiLink);

    private:
        Interval interval;
        std::shared_ptr<AnyBase> data;
        Key* singleLink;
        std::vector<Key*> multiLink;
    };
}

#endif //IBPTREE_KEY_HPP
