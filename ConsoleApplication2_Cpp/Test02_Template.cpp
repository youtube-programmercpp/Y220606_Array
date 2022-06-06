#include <iostream>
#include <stdexcept>
template<class T, size_t N>class Array {
	T data[N];
public:
	constexpr size_t size() const noexcept
	{
		return N;
	}
	T& operator[](size_t i)
	{
		if (i < N)
			return data[i];
		else
			throw std::out_of_range("配列の範囲を超えました。");
	}
	const T& operator[](size_t i) const
	{
		if (i < N)
			return data[i];
		else
			throw std::out_of_range("配列の範囲を超えました。");
	}
};
template<class T, size_t N>void DumpArray(const Array<T, N>& a)
{
	for (size_t i = 0; i < N; ++i)
		std::cout << a[i] << '\n';
}
int main()
{
	try {
		Array<int, 10> a;
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
