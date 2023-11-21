#ifndef NBTTAG_H
#define NBTTAG_H
#include <vector>
#include <string>

using namespace std;

constexpr uint8_t NBT_TAG_LENGTH = 1;
constexpr uint8_t NBT_NAME_LENGTH_LENGTH = 4;

enum NbtType {
    END, BYTE, SHORT, INT, LONG, FLOAT, DOUBLE, BYTE_ARRAY, STRING, LIST, COMPOUND, INT_ARRAY, LONG_ARRAY
};

class NbtTag {
protected:
    NbtType type;
    bool is_named;
    string name;

    virtual bool is_nested_type() = 0;

public:
    NbtTag(const NbtType type)
        : type(type),
          is_named(false) {
    }
    NbtTag(const NbtType type, const string name)
            : type(type),
              is_named(true),
              name(name) {
    }
    NbtTag(uint8_t * binary) {}
    ~NbtTag() = default;
    uint16_t get_tag() const;
    virtual size_t get_size() const = 0;
    virtual string to_string() const = 0;
};

class SimpleNbtTag : public NbtTag {
    bool is_nested_type() override;

public:
    SimpleNbtTag(NbtType type)
        : NbtTag(type) {
    }
    SimpleNbtTag(NbtType type, const string name)
            : NbtTag(type, name) {
    }
    size_t get_size() const override;
    string to_string() const override;
};

typedef SimpleNbtTag EndNbtTag;



template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic_v<T>>
>
class NumericalNbtTag : public SimpleNbtTag {
    T value;
public:
    NumericalNbtTag(NbtType type, T value) : SimpleNbtTag(type), value(value) {}
    NumericalNbtTag(NbtType type, const string name, T value) : SimpleNbtTag(type, name), value(value) {}
    size_t get_size() const override;
    string to_string() const override;
};

template<typename T, typename T0>
size_t NumericalNbtTag<T, T0>::get_size() const {
    const size_t size = NBT_TAG_LENGTH + sizeof(T);
    return is_named ? NBT_NAME_LENGTH_LENGTH + name.size() * 2 + size : size;
}

template<typename T, typename T0>
string NumericalNbtTag<T, T0>::to_string() const {
    return is_named ? name + ": " + std::to_string(value) + "\n" : std::to_string(value) + "\n";
}



template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic_v<T>>
>
class ArrayNbtTag : public SimpleNbtTag {
    vector<T> values;
public:
    ArrayNbtTag(NbtType type, vector<T> values) : SimpleNbtTag(type), values(values) {}
    ArrayNbtTag(NbtType type, const string name, vector<T> values) : SimpleNbtTag(type), values(values) {}
    size_t get_size() const override;
    string to_string() const override;
};



class NestedNbtTag : public NbtTag {
    vector<NbtTag *> tags_;
    bool is_nested_type() override;
public:
    NestedNbtTag(NbtType type, vector<NbtTag *> tags) : NbtTag(type), tags_(tags) {}
    NestedNbtTag(NbtType type, const string name, vector<NbtTag *> tags) : NbtTag(type, name), tags_(tags) {}

    size_t get_size() const override;
    string to_string() const override;

    vector<NbtTag *> tags() const {
        return tags_;
    }
};



#endif //NBTTAG_H
