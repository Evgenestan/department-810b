#include <iostream>
#include <thread>
#include <vector> 
#include <chrono>
#include <algorithm>
const int n = 100000;

int main(){

	std::vector<std::thread> threads;
	std::vector<double> numbers(n);
	auto start = std::chrono::high_resolution_clock::now();
	for(size_t i = 0; i< std::thread::hardware_concurrency();++i){
		threads.emplace_back([&, thread_id = i](){
			const int threads_num = std::thread::hardware_concurrency();
			const int begin = n/ threads_num * thread_id+std::min<int>(thread_id, n% threads_num);
			const int end = n/ threads_num*(thread_id+1)+std::min<int>(thread_id+1, n % threads_num);
			for(int i = begin; i<end; i++){
				numbers[i] = i;
			}
		});
	}
	for(size_t i = 0; i< std::thread::hardware_concurrency();++i){
		threads[i].join();
	}
	auto finish = std::chrono::high_resolution_clock::now();
	auto delta =  std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
	std::cout << delta.count() <<std::endl;

	std::cout<<"Maximum of thread: "<<std::thread::hardware_concurrency()<<std::endl;


}