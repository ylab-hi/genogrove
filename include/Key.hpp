#ifndef IBPTREE_KEY_HPP
#define IBPTREE_KEY_HPP

// Standard
#include <memory>
#include <vector>

// Class
#include "DataTypes.hpp"

class Key {
    public:
        Key(dtp::Interval interval);
        Key(dtp::Interval interval, std::shared_ptr<void> data);
        ~Key();

        bool operator<(const Key& other) const;
        bool operator>(const Key& other) const;

        // getter & setter
        dtp::Interval getInterval();
        void setInterval(dtp::Interval interval);
        std::shared_ptr<void> getData();
        void setData(std::shared_ptr<void> data);
        Key* getSingleLink();
        void setSingleLink(Key* singleLink);
        std::vector<Key*> getMultiLink();
        void setMultiLink(std::vector<Key*> multiLink);

    private:
        dtp::Interval interval;
        std::shared_ptr<void> data;
        Key* singleLink;
        std::vector<Key*> multiLink;
};

#endif //IBPTREE_KEY_HPP
