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

namespace genogrove {
    class Interval; // forward declaration

    class AnyBase {
        public:
            virtual ~AnyBase() = default;

            virtual std::string getDataTypeName() const = 0; // return name of stored type
            virtual std::type_index getDataType() const = 0; // return type of stored data
            virtual bool hasData() const = 0;
    };

    template<typename T>
    class AnyType : public AnyBase {
        private:
            std::optional<T> data;
            std::type_index dataType;

        public:
            // constructors
            AnyType() : dataType(typeid(T)) {}
            AnyType(const T& value) : data(value), dataType(typeid(T)) {} // Constructor for lvalue references
            AnyType(T&& data) : data(std::move(data)) {}
            ~AnyType() override = default; // needs to be defined explicitly (otherwise delete due to use of std::optional)

            const T& getData() const { return *data; }
            T& getData() { return *data; }

            std::string getDataTypeName() const { return typeid(T).name();}
            std::type_index getDataType() const { return dataType; }
            void setDataType(std::type_index datatype) { dataType = datatype; }
            bool hasData() const override { return data.has_value(); }
    };

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
                TypeRegistry::instance().registerType(typeid(T).name(), typeid(T));
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
