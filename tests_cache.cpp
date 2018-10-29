#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "cache.hh"

TEST_CASE("Create cache set/get value.","[single-file]")
{
    const Cache::key_type key1 = "one";
    const int val = 1;
    const Cache::val_type point1 = &val;
    const Cache::index_type size = sizeof(val);
    Cache new_cache(1000);
    Cache::index_type sized;
    new_cache.set(key1, point1, size);
    Cache::val_type thepoint = new_cache.get(key1, sized);
    const uint32_t &theval = *(static_cast<const u_int32_t *>(thepoint));
    SECTION("A value in the cache can be retrieved and its size is stored in the address.")
    {
        const Cache::key_type key1 = "one";
        const int val = 1;
        const Cache::val_type point1 = &val;
        const Cache::index_type size = sizeof(val);
        Cache new_cache(1000);
        Cache::index_type sized;
        
        // Set the value
        new_cache.set(key1, point1, size);

        // Get the value
        Cache::val_type the_point = new_cache.get(key1, sized);
        const uint32_t &theval = *(static_cast<const u_int32_t *>(thepoint));

        REQUIRE(theval == val);
        REQUIRE(sized == size);
    }
    SECTION("Getting a value not in the cache returns null.")
    {
        const Cache::key_type key1 = "one";
        Cache new_cache(1000);
        Cache::index_type sized;
        
        Cache::val_type the_point = new_cache.get(key1, sized);
        REQUIRE(!the_point);
    }
}