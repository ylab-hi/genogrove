#ifndef GENOGROVE_TYPEDDATA_HPP
#define GENOGROVE_TYPEDDATA_HPP

template<typename T>
class TypedData {
    public:
        TypedData(T data) : data(data) {}
        ~TypedData() {}

    private:
        T data;
};

#endif //GENOGROVE_TYPEDDATA_HPP
