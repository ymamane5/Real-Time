#include<stdio.h>
#include <dlfcn.h>

int main()
{
	void* handle;
	void (*lib1func)();

	handle = dlopen("./libN.so", RTLD_LAZY);

	if(!handle)
		printf("Eror: cannot open libray\n");


	*(void**)(&lib1func) = dlsym(handle, "lib1func");
	if(!lib1func)
		printf("dlsym failed\n");
	else
		lib1func();

	dlclose(handle);
}