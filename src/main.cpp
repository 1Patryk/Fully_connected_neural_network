#include "../Include/Fully_connected_network.hpp"
#include <QApplication>
#include <QWidget>

int main(int argc, char* argv[])
{
	auto Start = std::chrono::high_resolution_clock::now();

	QApplication app(argc, argv);
	QWidget Window;

	Window.resize(320, 240);
	Window.show();
	Window.setWindowTitle(
		QApplication::translate("toplevel", "Top-level widget"));

	Fully_connected_network DATA;				

	DATA.Calculating_the_network_MLP();

	//DATA.Display_results_for_MLP();

	auto Stop = std::chrono::high_resolution_clock::now();
	DATA.Display_results_counting_time(Start, Stop, "Cumulatively", 2);

	return app.exec();
}