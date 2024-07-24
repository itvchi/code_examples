#include <iostream>
#include <array>

/* This example compiles withat least --std=c++17 */

enum class IndexEnum {
    First,
    Second,
    Third
};

struct DataType {
    std::string text;
    int value;
};

namespace example {
    template <typename... ValidKeys>
    struct EnumTypeDeduce;

    template <typename FirstKey, typename... RestKeys>
    struct EnumTypeDeduce<FirstKey, RestKeys...> {
        using type = std::decay_t<FirstKey>;
        static_assert((std::is_same_v<type, std::decay_t<RestKeys>> && ...), "All valid keys must be of the same enum type.");
        static_assert(std::is_enum_v<type>, "Valid keys must be enum values.");
    };

    template <typename DataType, auto... ValidKeys>
    class enum_array {
        static constexpr std::size_t key_quantity = sizeof...(ValidKeys);
        static_assert(key_quantity > 0, "At least one valid key must be specified.");

        using EnumType = typename EnumTypeDeduce<decltype(ValidKeys)...>::type;
        
        static constexpr std::array<EnumType, key_quantity> index2enum = { ValidKeys... };
        
        constexpr static std::size_t index(EnumType key) {
            for (std::size_t idx = 0; idx < key_quantity; ++idx) {
                if (index2enum[idx] == key) {
                    return idx;
                }
            }
            throw std::out_of_range("Invalid enum key access.");
        }

        class iterator {
            enum_array& array_ref;
            std::size_t current_index;

            public:
                iterator(enum_array& array, std::size_t index) 
                    : array_ref{array}, current_index{index} {}

                std::pair<const EnumType&, DataType&> operator*() {
                    return {array_ref.index2enum[current_index], array_ref.data[current_index]};
                }

                iterator& operator++() {
                    ++current_index;
                    return *this;
                }

                bool operator!=(const iterator& other) const {
                    return (current_index != other.current_index);
                }
        };

        std::array<DataType, key_quantity> data{};

        public:
            enum_array() = default;

            DataType& operator[](EnumType key) {
                return data[index(key)];
            }

            const DataType& operator[](EnumType key) const {
                return data[index(key)];
            }

            std::size_t size() const {
                return key_quantity;
            }

            iterator begin() {
                return iterator(*this, 0);
            }

            iterator end() {
                return iterator(*this, key_quantity);
            }
    };
};

int main(int argc, char const *argv[]) {

    example::enum_array<DataType, IndexEnum::First, IndexEnum::Second> test_array;

    test_array[IndexEnum::First] = DataType{"first", 1};
    test_array[IndexEnum::Second] = DataType{"second", 2};

    try {
        test_array[IndexEnum::Third] = DataType{"third", 3};
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    for (auto [index, element] : test_array) {
        std::cout << "test_array[" << static_cast<int>(index) << "] = " << element.text << std::endl;
    }

    return 0;
}
