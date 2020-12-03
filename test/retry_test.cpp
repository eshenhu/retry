#define BOOST_TEST_MODULE retry_test

#include <boost/test/unit_test.hpp>
#include "../retry.hpp"

BOOST_AUTO_TEST_SUITE(retry_test);

BOOST_AUTO_TEST_CASE(retry_with_exit_inloop) {
    int n = 0;
    retry([&](){
        return (++n > 5) ? true : false;
    })
    .withN(2)
    .run();

    BOOST_REQUIRE_EQUAL(n, 2);
}

BOOST_AUTO_TEST_CASE(retry_with_exit_inrules) {
    int n = 0;
    retry([&](){
        return (++n > 3) ? true : false;
    })
    .withN(9)
    .run();

    BOOST_REQUIRE_EQUAL(n, 4);
}

BOOST_AUTO_TEST_CASE(retry_with_roll_exit_inrules) {
    int n = 0;
    retry([&](){
        return (++n > 3) ? true : false;
    })
    .withRoll([&](){
        n = -1;
    })
    .withN(9)
    .run();

    BOOST_REQUIRE_EQUAL(n, 4);
}

BOOST_AUTO_TEST_CASE(retry_with_roll_exit_inloop) {
    int n = 0;
    retry([&](){
        return (++n > 5) ? true : false;
    })
    .withRoll([&](){
        n = -1;
    })
    .withN(2)
    .run();

    BOOST_REQUIRE_EQUAL(n, -1);
}

BOOST_AUTO_TEST_SUITE_END()