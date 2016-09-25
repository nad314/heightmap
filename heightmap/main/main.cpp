#include <main/main.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
//int main(void) {
	return core::Init()(new Program);
}
