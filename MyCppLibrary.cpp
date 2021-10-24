// MyCppLibrary.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


// #ifndef PRIME_202110172314
// #define PRIME_202110172314

#include <iostream>
#include <functional>
#include <vector>
#include <cmath>

struct Identity {
	template<class T>
	constexpr decltype(auto) operator()(T&& t) const noexcept {
		return std::forward<T>(t);
	}
};

template<class TypeDate,typename TypeFunc = Identity> bool isPrime(const TypeDate& n,TypeFunc fSqrt = {},const bool debug = false) {
	static_assert(std::is_integral<TypeDate>::value,"\n!! Integral Value Necessary !!\n");
	static std::vector<TypeDate> primes{2,3,5,7};
	if(n<=1) {
		return false;
	}
	if constexpr(!std::is_same_v<TypeFunc,Identity>) {
		float nSqrt{fSqrt(n)};
		struct IncorrectSqrt {
			TypeDate _n;
			float _nSqrt;
			IncorrectSqrt(TypeDate n = 0,float nSqrt = 0.0) : _n(n),_nSqrt(nSqrt) {};
		};
		if(float nSqrtSq{nSqrt*nSqrt};!(n-1<nSqrtSq&&nSqrtSq<n+1)) {
			if(debug) {  // ‘debug’ is not a constant expression   // want to use if-constexpr
				std::cout<<"\n!! Sqrt Calculation Error !!\n";
			}
			throw IncorrectSqrt();
		}
		for(const TypeDate& prime:primes) {
			if(n%prime==0) {
				return n==prime;
			}
			if(nSqrt<prime) {
				return true;
			}
		}
		TypeDate last{primes.back()};
		while(last<nSqrt) {
			do {
				last += 2;
			} while(!isPrime(last,fSqrt));
			primes.push_back(last);
			if(debug) {
				std::cout<<" (Pushing:"<<last<<")\n";
			}
			if(n%last==0) {
				return n==last;
			}
		}
	}
	else {
		for(const TypeDate& prime:primes) {
			if(n%prime==0) {
				return n==prime;
			}
			if(n<prime*prime) {
				return true;
			}
		}
		TypeDate last{primes.back()};
		while(last*last<n) {
			do {
				last += 2;
			} while(!isPrime(last,fSqrt));
			primes.push_back(last);
			if(debug) {
				std::cout<<" (Pushing:"<<last<<")\n";
			}
			if(n%last==0) {
				return n==last;
			}
		}
	}
	return true;
}

//*	toggle 1, of 2, slash(s) to turn main on/off
int main() {
	int n{};
	std::cout<<std::endl<<"\"prime.cpp\"\n\nNumber: ";
	std::cin>>n;
	auto fSqrt = [](decltype(n) v) {return std::sqrt(static_cast<float>(v));};
	std::cout<<(isPrime(n)?"Positive":"Negative")<<'\n';
	for(int i{};i<n;++i)
		if(isPrime(i,fSqrt))
			std::cout<<' '<<i;
	std::cout<<std::endl;
	return 0;
}
//*/

// #endif


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
