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

namespace genogrove {
    class Interval; // forward declaration

    class AnyBase {
        public:
            virtual ~AnyBase() = default;
            virtual std::string getTypeName() const = 0;
            virtual bool hasData() const = 0;
            virtual std::any getAnyData() const = 0;
    };

    template<typename T>
    class AnyType : public AnyBase {
        private:
            std::optional<T> data;

        public:
            AnyType() = default;
            AnyType(const T& value) : data(value) {} // Constructor for lvalue references
            AnyType(T&& data) : data(std::move(data)) {}
            ~AnyType() override = default; // needs to be defined explicitly (otherwise delete due to use of std::optional)

            const T& getData() const { return *data; }
            T& getData() { return *data; }
            std::string getTypeName() const override { return typeid(T).name();}
            bool hasData() const override { return data.has_value(); }
    };

    class Key {
    public:
        Key();
        Key(Interval interval);
        template<typename T>
        Key(Interval intvl, T&& data) {
            this->interval = intvl;
            this->



//            this->data = std::make_shared<AnyType<std::decay_t<T>>>(std::forward<T>(data));
//            this->singleLink = nullptr;
//            this->multiLink = std::vector<Key*>();
        }
        ~Key();

        bool operator<(const Key& other) const;
        bool operator>(const Key& other) const;

        // getter & setter
        Interval getInterval();
        void setInterval(Interval interval);
        std::shared_ptr<AnyBase> getData();
        void setData(std::shared_ptr<AnyBase> data);
        std::type_index getDataType();
        void setDataType(std::type_index datatype);
        Key* getSingleLink();
        void setSingleLink(Key* singleLink);
        std::vector<Key*> getMultiLink();
        void setMultiLink(std::vector<Key*> multiLink);

    private:
        Interval interval;
        std::shared_ptr<AnyBase> data;
        std::type_index dataType;
        Key* singleLink;
        std::vector<Key*> multiLink;
    };
}

#endif //IBPTREE_KEY_HPP
