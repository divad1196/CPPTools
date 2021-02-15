#include <cstdlib>
#include <cstring>
#include <string>
#include <map>
#include <iostream>

template<typename KeyT = std::string>
class PairBuilder {
    public:
        PairBuilder(const KeyT& key): _key(key) {}
        PairBuilder(const char* key, std::size_t size): PairBuilder(KeyT(key, size)) {}
        PairBuilder(const char* key): PairBuilder(KeyT(key, strlen(key))) {}

        template<typename ValueT>
        std::pair<KeyT, ValueT> operator <=(const ValueT& value) {
            return {_key, value};
        }

    private:
        const KeyT _key;
};


PairBuilder<std::string> operator ""_ks(const char* str, size_t size) {
    return PairBuilder<std::string>(str, size);
};



int main() {

    auto t = "mykey"_ks <= 4;
    //~ auto t = PairBuilder("mykey") <= 4;

    std::cout << t.first << " " << t.second << std::endl;

    std::map<std::string, int> mymap = {
        "foo"_ks <= 4,
        "bar"_ks <= 7,
        "helloworld"_ks <= 4,
        "test"_ks <= 0,
    };

    std::map<std::string, int> mymap2 = {
        {"foo",  4},
        {"bar", 7},
        {"helloworld", 4},
        {"test", 0},
    };


    return EXIT_SUCCESS;
}
