#include "qt_visualization/plane_calibration_ui.hpp"

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QPushButton>

#include <memory>
#include <string>

using namespace qt_visualization;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  PlaneCalibrationUI main_window;
  main_window.show();

  return app.exec();
}
