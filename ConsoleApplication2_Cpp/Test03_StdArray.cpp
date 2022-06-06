#include <iostream>
#include <array>
#include <stdexcept>
template<class T, size_t N>void DumpArray(const std::array<T, N>& a)
{
	for (size_t i = 0; i < N; ++i)
		std::cout << a[i] << '\n';
}
int main()
{
	try {
		std::array<int, 10> a;
		for (size_t i = 0; i < a.size(); ++i)
			a[i] = 0;
		DumpArray(a);
		//a[-1] = 0;
		a[10] = 0;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}
