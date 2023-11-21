#include "NbtTag.h"


uint16_t NbtTag::get_tag() const {
    switch (this->type) {
        case END: return 0x0;
        case BYTE: return 0x1;
        case SHORT: return 0x2;
        case INT: return 0x3;
        case LONG: return 0x4;
        case FLOAT: return 0x5;
        case DOUBLE: return 0x6;
        case BYTE_ARRAY: return 0x7;
        case STRING: return 0x8;
        case LIST: return 0x9;
        case COMPOUND: return 0xa;
        case INT_ARRAY: return 0xb;
        case LONG_ARRAY: return 0xc;
        default: throw runtime_error("Unknown NBT tag type: " + std::to_string(type));
    }
}

NbtTag NbtTag::from_binary(uint8_t *binary) const {
    uint16_t
}

size_t EndNbtTag::get_size() const {
    return 0;
}

string EndNbtTag::to_string() const {
    return "}\n";
}





template<typename T, typename T0>
size_t ArrayNbtTag<T, T0>::get_size() const {
    const size_t size = NBT_TAG_LENGTH + sizeof(T) * values.size();
    return is_named ? NBT_NAME_LENGTH_LENGTH + name.size() * 2 + size : size;
}

template<typename T, typename T0>
string ArrayNbtTag<T, T0>::to_string() const {
    return is_named ? name + ": " + std::to_string(values) + "\n" : std::to_string(values) + "\n";
}

size_t NestedNbtTag::get_size() const {
    size_t size = NBT_TAG_LENGTH;
    for (NbtTag * tag : tags_) {
        size += tag->get_size();
    }
    return is_named ? NBT_NAME_LENGTH_LENGTH + name.size() * 2 + size : size;
}

string NestedNbtTag::to_string() const {
    string val = is_named ? name + ": {\n" : "{\n";
    for (NbtTag * tag : tags()) {
        val += "\t" + tag->to_string();
    }
    return val;
}

bool SimpleNbtTag::is_nested_type() {
    return false;
}

bool NestedNbtTag::is_nested_type() {
    return true;
}








