//
// Created by Guillaume Guerin on 2019-03-08.
//

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include "./testdemo.cpp"

BOOST_AUTO_TEST_CASE( test1 )
{
	BOOST_TEST( add(20, 0) == 25 );
}
