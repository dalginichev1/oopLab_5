#include "forwardList.hpp"
#include "customAllocator.hpp"

#include <gtest/gtest.h>

TEST(ForwardListTest, CreateAndDestroy) {
    FixedCustomMemoryResource resource(1000);
    {
        ForwardList<int> list(&resource);
        EXPECT_TRUE(list.empty());
    }
}

TEST(ForwardListTest, PushFront) {
    FixedCustomMemoryResource resource(1000);
    ForwardList<int> list(&resource);
    
    list.push_front(10);
    EXPECT_FALSE(list.empty());
    
    list.push_front(20);
    list.push_front(30);
 
    auto it = list.begin();
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 10);
}

TEST(ForwardListTest, PopFront) {
    FixedCustomMemoryResource resource(1000);
    ForwardList<int> list(&resource);
    
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    
    list.pop_front();
    EXPECT_EQ(*list.begin(), 20);
    
    list.pop_front();
    EXPECT_EQ(*list.begin(), 10);
    
    list.pop_front();
    EXPECT_TRUE(list.empty());
}

TEST(ForwardListTest, Clear) {
    FixedCustomMemoryResource resource(1000);
    ForwardList<int> list(&resource);
    
    for (int i = 0; i < 5; ++i) {
        list.push_front(i);
    }
    
    EXPECT_FALSE(list.empty());
    list.clear();
    EXPECT_TRUE(list.empty());
}

TEST(ForwardListTest, IterateEmptyList) {
    FixedCustomMemoryResource resource(1000);
    ForwardList<int> list(&resource);
    
    int count = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 0);
}

TEST(ForwardListTest, IterateFilledList) {
    FixedCustomMemoryResource resource(1000);
    ForwardList<int> list(&resource);
    
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    
    std::vector<int> result;
    for (const auto& item : list) {
        result.push_back(item);
    }
    
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
}

TEST(ForwardListTest, MoveSemantics) {
    FixedCustomMemoryResource resource(1000);
    ForwardList<std::string> list(&resource);
    
    std::string str = "Hello";
    list.push_front(std::move(str));
    
    EXPECT_TRUE(str.empty()); 
    EXPECT_EQ(*list.begin(), "Hello");
}

TEST(ForwardListTest, CopySemantics) {
    FixedCustomMemoryResource resource(1000);
    ForwardList<int> list1(&resource);
    
    list1.push_front(1);
    list1.push_front(2);

}

TEST(ForwardListTest, DifferentDataTypes) {
    FixedCustomMemoryResource resource(1000);
    ForwardList<double> doubleList(&resource);
    
    doubleList.push_front(3.14);
    doubleList.push_front(2.71);
    
    EXPECT_EQ(*doubleList.begin(), 2.71);
    
    ForwardList<std::string> stringList(&resource);
    stringList.push_front("World");
    stringList.push_front("Hello");
    
    EXPECT_EQ(*stringList.begin(), "Hello");
}

TEST(ForwardListTest, MemoryExhaustion) {
    FixedCustomMemoryResource resource(1000); 
    
    ForwardList<int> list(&resource);

    for (int i = 0; i < 10; ++i) {
        list.push_front(i);
    }

    EXPECT_FALSE(list.empty());
}

TEST(ForwardListTest, IteratorOperations) {
    FixedCustomMemoryResource resource(1000);
    ForwardList<int> list(&resource);
    
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    
    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    
    ++it;
    EXPECT_EQ(*it, 2);
    
    auto it2 = it++;
    EXPECT_EQ(*it2, 2);
    EXPECT_EQ(*it, 3);
}

TEST(ForwardListTest, ConstIterators) {
    FixedCustomMemoryResource resource(1000);
    ForwardList<int> list(&resource);
    
    list.push_front(42);
    
    const ForwardList<int>& const_list = list;
    auto it = const_list.begin();
    EXPECT_EQ(*it, 42);
    
}

TEST(ForwardListTest, MultipleOperations) {
    FixedCustomMemoryResource resource(1000);
    ForwardList<int> list(&resource);

    list.push_front(1);
    list.push_front(2);
    list.pop_front();
    list.push_front(3);
    list.push_front(4);
    list.pop_front();
    list.push_front(5);
    
    std::vector<int> expected = {5, 3, 1};
    std::vector<int> actual;
    
    for (const auto& item : list) {
        actual.push_back(item);
    }
    
    EXPECT_EQ(actual, expected);
}

TEST(ForwardListTest, DestructorNoThrow) {
    FixedCustomMemoryResource resource(1000);
    
    EXPECT_NO_THROW({
        ForwardList<int> list(&resource);
        list.push_front(1);
        list.push_front(2);
    });
}

struct TestStruct {
    int id;
    std::string name;
    TestStruct(int i, const std::string& n) : id(i), name(n) {}
};

TEST(ForwardListTest, CustomStruct) {
    FixedCustomMemoryResource resource(1000);
    ForwardList<TestStruct> list(&resource);
    
    list.push_front(TestStruct(1, "First"));
    list.push_front(TestStruct(2, "Second"));
    
    EXPECT_EQ(list.begin()->id, 2);
    EXPECT_EQ(list.begin()->name, "Second");
}
