/*
** EPITECH PROJECT, 2019
** CPP_zia_github
** File description:
** HttpHeader
*/

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include "utils/DLLoader.hpp"
#include "HttpHeader.hpp"

namespace Zia {

BOOST_AUTO_TEST_SUITE( ZIATests )

BOOST_AUTO_TEST_CASE(DLLoaderUnknown)
{
  std::cerr << "Building tests for Unknown" << std::endl;
  BOOST_CHECK_THROW(DLLoader("./build/lib/libmod_RANDOM.so"), std::runtime_error);
  std::cerr << "Done." << std::endl;
}

BOOST_AUTO_TEST_CASE(Header) {
  std::cerr << "Building test for Header" << std::endl;
  HttpHeader head;
  head.setHeader("test", "value");
  BOOST_CHECK(head["test"] == "value");
  std::cerr << "End tests for Header" << std::endl;
}

BOOST_AUTO_TEST_CASE(DLLoaderGUILogger)
{
  std::cerr << "Building tests for GUILogger" << std::endl;
	BOOST_CHECK_NO_THROW({DLLoader loader("./build/lib/libmod_guiLogger.so");});
  std::cerr << "Done." << std::endl;
}

BOOST_AUTO_TEST_CASE(DLLoaderLogger)
{
  std::cerr << "Building tests for logger" << std::endl;
	BOOST_CHECK_NO_THROW({DLLoader loader("./build/lib/libmod_logger.so");});
  std::cerr << "Done." << std::endl;
}

BOOST_AUTO_TEST_CASE(DLLoaderTimeProcessing)
{
  std::cerr << "Building tests for TimeProcessing" << std::endl;
	BOOST_CHECK_NO_THROW({DLLoader loader("./build/lib/libmod_timeProcessing.so");});
  std::cerr << "Done." << std::endl;
}

BOOST_AUTO_TEST_CASE(DLLoaderHTTP)
{
  std::cerr << "Building tests for HTTP" << std::endl;
	BOOST_CHECK_NO_THROW({DLLoader loader("./build/lib/libmod_http.so");});
  std::cerr << "Done." << std::endl;
}

BOOST_AUTO_TEST_CASE(DLLoaderPHP)
{
  // std::cerr << "Building tests for PHP" << std::endl;
	// //BOOST_CHECK_NO_THROW({DLLoader loader("./build/lib/libmod_php.so");});
  // std::cerr << "Done." << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()

}