#include <iostream>
#include <stdexcept>
#define	N	10
class Array {
	int data[N];
public:
	int& operator[](size_t i)
	{
		if (i < N)
			return data[i];
		else
			throw std::out_of_range("配列の範囲を超えました。");
	}
	const int& operator[](size_t i) const
	{
		if (i < N)
			return data[i];
		else
			throw std::out_of_range("配列の範囲を超えました。");
	}
};
void DumpArray(const Array& a)
{
	for (size_t i = 0; i < N; ++i)
		std::cout << a[i] << '\n';
}
int main()
{
	try {
		Array a;
		for (size_t i = 0;i < N;++i)
			a[i] = 0;
		DumpArray(a);
		//a[-1] = 0;
		a[10] = 0;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}
