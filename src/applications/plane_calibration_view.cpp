#include "qt_visualization/plane_calibration_ui.hpp"

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QPushButton>

#include <memory>
#include <string>

using namespace qt_visualization;

std::unique_ptr<QWidget> setupWindow(std::string title)
{
  QDesktopWidget* desktop = QApplication::desktop();
  int screen_width = desktop->width();
  int screen_height = desktop->height();

  std::unique_ptr<QWidget> window = std::unique_ptr<QWidget>(new QWidget());

  window->resize(screen_width, screen_height);
  window->move(screen_width / 2, screen_height / 2);
  window->setWindowTitle(QString::fromStdString(title));

  return window;
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

//  std::unique_ptr<QWidget> main_window = setupWindow("Plane Calibration View");
  PlaneCalibrationUI main_window;// = setupWindow("Plane Calibration View");

  main_window.show();

  return app.exec();
}
