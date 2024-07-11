#ifndef IBPTREE_KEY_HPP
#define IBPTREE_KEY_HPP

// Class
#include "DataTypes.hpp"

class Key {
    public:
        Key();
        ~Key();

    private:
        dtp::Interval interval;
        std::shared_ptr<void> data;
        Key* singleLink;
        std::vector<Key*> multiLink;
};

#endif //IBPTREE_KEY_HPP
