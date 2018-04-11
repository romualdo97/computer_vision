#pragma once

#ifdef FACETRACKERLIB_EXPORTS
#define FACETRACKERLIB_API __declspec(dllexport)
#else
#define FACETRACKERLIB_API __declspec(dllimport)
#endif // FACETRACKERLIB_EXPORTS

extern "C"
{
	FACETRACKERLIB_API char* sayHello();
}