/*
 * Hoge.ccのテスト
 */
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

#include "../Hoge.h"

class HogeTest : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(HogeTest);
	CPPUNIT_TEST(testMyFunc1);
	CPPUNIT_TEST(testMyFunc2);
	CPPUNIT_TEST_SUITE_END();

	private:
		Hoge *f;

	public:

		// 各テストケースの実行直前に呼ばれる
		void setUp (){
			f = new Hoge();
		}

		// 各テストケースの実行直後に呼ばれる
		void tearDown(){
			delete f;
		}

		// Hoge::myfunc1()のテスト
		void testMyFunc1() {
			// テストの結果が正しければ真となる式を記述します。
			CPPUNIT_ASSERT( f->myfunc1() == 1 );
			CPPUNIT_ASSERT_MESSAGE("error message", f->myfunc1() == 1 );
		}
		
		// Hoge::myfunc2()のテスト
		void testMyFunc2() {
			CPPUNIT_ASSERT_EQUAL(f->myfunc2(), 2);
		}

};

// テストを追加する際に必要です。これがないと、テスト実行してもこのテストが認識されません。
CPPUNIT_TEST_SUITE_REGISTRATION(HogeTest);
