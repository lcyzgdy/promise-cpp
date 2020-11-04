// primise-cpp.test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include "Promise.hpp"

int main()
{
	Promise::Promise<void> a([](std::function<void()>&& resolve)->void {
		std::cout << "Hello World!\n";
		resolve();
	});
}