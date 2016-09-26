#include <main/main.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
//int main(void) {
	core::Debug::enable();
	return core::Init()(new Program);
}
