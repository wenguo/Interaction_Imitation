#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <string>
using namespace std;

string convBase(uint16_t v, long base);
double simple_normal_deviate( double mean, double stddev );
inline int sign(int num) { return num<0 ? -1 : 1;};
void PrintBuffer(uint8_t *data, int size);


class Hist
{
	public:
		Hist(uint8_t s = 64);
		~Hist();

		void Reset();
		void Resize(uint8_t s);

		void Push(int value);

		inline int Avg() {return sum / size;}

		inline long Sum(){return sum;}

		void Print();

	private:
		long sum;
		int *valueHist;
		uint8_t valPointer;
		uint8_t size;

} ;


#endif
