#ifndef IBPTREE_KEY_HPP
#define IBPTREE_KEY_HPP

// Standard
#include <memory>
#include <vector>

// Class
#include "DataTypes.hpp"
#include "Interval.hpp"

namespace genogrove {
    class Interval; // forward declaration

    class AnyBase {
        virtual ~AnyBase() = default;
        virtual std::string getTypeName() const = 0;
    };

    template<typename T>
    class AnyType : public AnyBase {
        private:
            T data;

        public:
            AnyType(T&& data) : data(std::move(data)) {}

            const T& getData() const { return data; }
            T& getDate() { return data; }

            std::string getTypeName() const override {
                return typeid(T).name();
            }
    };

    class Key {
    public:
        Key();
        Key(Interval interval);
        template<typename T>
        Key(Interval intvl, T&& data) {
            // ensure that T is always a non-referencen type
            using DataType = typename std::decay<T>::type;

            // create a new data element
            this->interval = intvl;
            this->data = std::make_shared<typename std::decay<T>::type>(std::forward<T>(data));
            this->singleLink = nullptr;
            this->multiLink = std::vector<Key*>();
        }
        ~Key();

        bool operator<(const Key& other) const;
        bool operator>(const Key& other) const;

        // getter & setter
        Interval getInterval();
        void setInterval(Interval interval);
        std::shared_ptr<void> getData();
        void setData(std::shared_ptr<void> data);
        Key* getSingleLink();
        void setSingleLink(Key* singleLink);
        std::vector<Key*> getMultiLink();
        void setMultiLink(std::vector<Key*> multiLink);

    private:
        Interval interval;
        std::shared_ptr<void> data;
        Key* singleLink;
        std::vector<Key*> multiLink;
    };
}

#endif //IBPTREE_KEY_HPP
