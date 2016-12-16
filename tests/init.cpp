#include <shared_ptr.cpp>
#include <catch.hpp>
#include <iostream>

SCENARIO("ctor1", "[ctor1]"){
  shared_ptr<int> sp;
  REQUIRE(!sp.get());
}

SCENARIO("reset", "[reset]"){
  shared_ptr<int> sp(new int(7));
  sp.reset();
}

SCENARIO("ctor2", "[ctor2]"){
  shared_ptr<int> sp(new int(7));
  REQUIRE(*sp==7);
  REQUIRE(sp.countref()==1);
}

SCENARIO("ctor3", "[ctor3]"){
  shared_ptr<int> sp1(new int(7));
  shared_ptr<int> sp2=sp1;
  REQUIRE(*sp2==7);
  REQUIRE(sp2.countref()==2);
}

SCENARIO("ctor4", "[ctor4]"){
  shared_ptr<int> sp1(new int(7));
  shared_ptr<int> sp2=std::move(sp1);
  REQUIRE(*sp2==7);
  REQUIRE(sp2.countref()==1);
}

SCENARIO("prisv1", "[prisv1]"){
  shared_ptr<int> sp1(new int(7));
  shared_ptr<int> sp2; 
  sp2=sp1;
  REQUIRE(*sp2==7);
  REQUIRE(sp2.countref()==2);
}

SCENARIO("prisv2", "[prisv2]"){
  shared_ptr<int> sp1(new int(7));
  shared_ptr<int> sp2;
  sp2=std::move(sp1);
  REQUIRE(*sp2==7);
  REQUIRE(sp2.countref()==1);
}

SCENARIO("swap", "[swap]"){
  shared_ptr<int> sp1(new int(7));
  shared_ptr<int> sp2(new int(77));
  sp1.swap(sp2);
  REQUIRE(*sp1==77);
  REQUIRE(*sp2==7);
}

SCENARIO("reset", "[reset]"){
  shared_ptr<int> sp(new int(7));
  sp.reset();
  REQUIRE(!sp.get());
}

SCENARIO("get", "[get]"){
  shared_ptr<int> sp(new int(7));
  REQUIRE(*sp.get()==7);
}

SCENARIO("op_CTPEJlO4KA", "op_CTPEJlO4KA[]"){
	class A{
	public:
		int a1;
		A(int x) : a1(x){}
	};
	A a(7);
	shared_ptr<A> sptr1=make_shared<A>(std::move(a));
	REQUIRE(sptr1->a1 == 7);
}

SCENARIO("op_3BE3DO4KA", "[op_3BE3DO4KA]"){
  shared_ptr<int> sp(new int(7));
  REQUIRE(*sp==7);
}

SCENARIO("countref", "[countref]"){
  shared_ptr<int> sp1(new int(7));
  shared_ptr<int> sp2=sp1;
  shared_ptr<int> sp3;
  sp3=sp2;
  REQUIRE(sp2.countref()==3);
}

SCENARIO("make_shared", "[make_shared]"){
  int a = 7;
	shared_ptr<int> sp = make_shared<int>(std::move(a));
  REQUIRE(*sp==7);
}

SCENARIO("test", "[test]"){
	shared_ptr<int> sptr1;
	shared_ptr<int> sptr2{ sptr1 };
REQUIRE(sptr2.countref()==0);
}
