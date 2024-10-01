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

/**
 * @file Key.hpp
 */
namespace genogrove {
    // \brief forward declaration of the Interval class
    class Interval; // forward declaration

    /**
     * @brief The Key class
     * @details The Key class is used to store the Key of the node in the IBPTree.
     */
    class Key {
    public:
        /**
         * @brief Default constructor
         */
        Key();
        /**
         * @brief Constructor for a key with an interval
         * @param Interval of the key
         */
        Key(Interval interval);
        /**
         * @brief Constructor of a key with an Interval and (arbitrary) data element
         * @param Interval of the key
         * @param data element of the key
         */
        template<typename T>
        Key(Interval intvl, T&& data) :
            interval(intvl),
            data(std::make_shared<AnyType<std::decay_t<T>>>(data)),
            singleLink(nullptr),
            multiLink(std::vector<Key*>()) {}
        /**
         * @brief Destructor of the Key class
         */
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

        // serialize the key
        void serialize(std::ostream& os) const;
        static Key deserialize(std::istream& is);

    private:
        Interval interval;
        std::shared_ptr<AnyBase> data;
        Key* singleLink;
        std::vector<Key*> multiLink;
    };
}

#endif //IBPTREE_KEY_HPP
