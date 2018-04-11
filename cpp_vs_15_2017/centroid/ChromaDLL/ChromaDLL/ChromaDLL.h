#define CHROMADLL_API __declspec(dllexport)

extern "C"
{
	CHROMADLL_API float getNumber();
	CHROMADLL_API void showCamera();
	CHROMADLL_API bool isCamera();
}