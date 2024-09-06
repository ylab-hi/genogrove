#ifndef GENOGROVE_TYPEDDATA_HPP
#define GENOGROVE_TYPEDDATA_HPP

template<typename T>
class TypedData {
    public:
        TypedData(T data) : data(data) {}
        ~TypedData() {}

        T getData() { return this->data; }

        void addData

    private:
        std::unordered_map<std::type_index, TypedData> typeMap;


        T data;
};

#endif //GENOGROVE_TYPEDDATA_HPP

class AnyTypedData {
private:
    std::unordered_map<std::type_index, std::vector<TypedData>>

};
