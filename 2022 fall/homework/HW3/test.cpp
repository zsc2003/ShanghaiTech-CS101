#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
namespace std {
template <>
inline void swap<int>(int &lhs, int &rhs) noexcept {
	auto tmp = lhs;
	lhs = rhs;
	rhs = tmp;
	std::cout << "swap is called.\n";
	}
} // namespace std
int main() {
	//std::srand(19260817);
	std::srand(time(0));
	constexpr int n = 16;
	std::vector<int> vec;
	for (auto i = 0; i != n; ++i){
		vec.push_back(std::rand());
		std::cout<<vec.back()<<' ';
	}
	std::sort(vec.begin(), vec.end());
	return 0;
}
