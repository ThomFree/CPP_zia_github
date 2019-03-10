# Unit test

There is an unit test demonstration using boost_unit_test_framework in demo.cpp, which test the ```add()``` function in testdemo.cpp

You can add your test with

```
BOOST_AUTO_TEST_CASE( testName )
{
	BOOST_TEST( 1 == 1 ); // Pass if true, fail if false
}
```

# Compilation

If your compilation failed, check if libstdc++ is use instead of libstdc++11
You can check it in ~/.conan/profiles/default
