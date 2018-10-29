#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "testinglab.cpp"

TEST_CASE("Set/Get","[single-file]")
{
    SECTION("A value in the cache can be retrieved.")
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
        const uint32_t &theval = *(static_cast<const u_int32_t *>(the_point));

        REQUIRE(theval == val);
    }
    SECTION("The size of the value returned is correct.")
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
        new_cache.get(key1, sized);
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

TEST_CASE("Space_used")
{
    SECTION("Ensure memused is 0 when no values are inserted.")
    {
        const Cache::key_type key1 = "one";
        const int val = 1;
        const Cache::val_type point1 = &val;
        const Cache::index_type size = sizeof(val);
        Cache new_cache(1000);
        Cache::index_type sized;
        
        // Set the value
        new_cache.set(key1, point1, size);

        // Get memused
        sized = new_cache.space_used();
        REQUIRE(sized == size);
    }
}

TEST_CASE("Del")
{
    SECTION("Delete removes the key/value from the cache.")
    {
        const Cache::key_type key1 = "one";
        const int val = 1;
        const Cache::val_type point1 = &val;
        const Cache::index_type size = sizeof(val);
        Cache new_cache(1000);
        Cache::index_type sized = 0;
            
        // Set the value
        new_cache.set(key1, point1, size);
        new_cache.del(key1);
        Cache::val_type the_point = new_cache.get(key1, sized);

        REQUIRE(sized == 0);
        REQUIRE(!the_point);
    }
    SECTION("Delete on k/v not in cache has no effect.")
    {
        const Cache::key_type key1 = "one";
        const Cache::key_type key2 = "two";

        const int val = 1;
        const Cache::val_type point1 = &val;
        const Cache::index_type size = sizeof(val);
        Cache new_cache(1000);
        Cache::index_type sized = size;
            
        // Set the value
        new_cache.set(key1, point1, size);
        new_cache.del(key2);
        Cache::val_type the_point = new_cache.get(key1, sized);
        const uint32_t &theval = *(static_cast<const u_int32_t *>(the_point));

        REQUIRE(size == new_cache.space_used());
        REQUIRE(theval == val);
    }
}