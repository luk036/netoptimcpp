#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do
                          // this in one cpp file
#include "catch2/catch.hpp"

#include <iostream>
#include <boost/coroutine2/all.hpp>
// #include <boost/coroutine2/detail/push_coroutine.hpp>
// #include <boost/coroutine2/detail/pull_coroutine.hpp>
using namespace std;

// 方法一

void foo(boost::coroutines2::coroutine<int>::pull_type & sink){
    // using coIter = boost::coroutines2::coroutine<int>::pull_type::iterator;
    for (auto start = begin(sink); start != end(sink); ++start) {
        std::cout << "retrieve "<<*start << "\n";
    }

}

// 方法二

void foo2(boost::coroutines2::coroutine<int>::pull_type & sink) {
    for (auto val : sink) {
        std::cout << "retrieve " << val << "\n";
    }
}

 

TEST_CASE("Test Coroutine", "[test_main]") {
    typedef boost::coroutines2::coroutine<int> coro_t;
    int max = 8;

    coro_t::pull_type source(
        [&](coro_t::push_type& sink){
            int first=1,second=1;
            sink(first);
            sink(second);
            for(int i=0;i<max;++i){
                int third=first+second;
                first=second;
                second=third;
                sink(third);
            }

        });

    for(auto i:source)
        cout << i <<  " ";
    cout << endl;

    coro_t::push_type sink(
        [&](coro_t::pull_type& source){
            while(source){
                cout << source.get() <<  " ";
                source();
            }
        });
    vector<int> v{1,1,2,3,5,8,13,21,34,55};
    copy(begin(v),end(v),begin(sink));

    foo(source);
}