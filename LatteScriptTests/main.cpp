#include <iostream>
#include "LatteScriptEngine.cpp"

LatteScriptEngine engine;

int main(int argc, char* argv[])
{
	engine = LatteScriptEngine();
	engine.executeCode(R"(
var base_pitch = master_pitch;
for(var i = 0; i <= 12; i++) {
	master_pitch = base_pitch + i;
	export_song("cathook_path_here" + str(i) + ".wav", true, true);
}
	)");
	std::cout << "Test";
	return 0;
}
