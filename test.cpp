#include <iostream>
#include <string.h>
using namespace std;
template <int size>
class test{
	//size_t size;
	public:
	char name[size];
};

int main(){
	FILE *fp = fopen("yangkai.txt","wb+");
	//struct test a;
	//a.name = new char [32];
	//a.size = 32;
	test<32> a;
	strcpy(a.name,"hello world");
	fwrite(&a,32+sizeof(size_t),1,fp);
	//fwrite(a.name,32,1,fp);
	fclose(fp);
	printf("%x\n",a.name);
	return 0;
}
