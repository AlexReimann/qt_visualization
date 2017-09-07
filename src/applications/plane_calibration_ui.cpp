#include <qt_visualization/plane_calibration_ui.hpp>

namespace qt_visualization
{

PlaneCalibrationUI::PlaneCalibrationUI()
{
  setupUi(this);
  setWindowTitle("PlaneCalibrationUI");
//  QObject::connect(QApplication::instance(), SIGNAL(aboutToQuit()), this, SLOT(writeSettings()));
//  QObject::connect(&widget_qgl_viewer->origin_teleport_arrow, SIGNAL(deactivated()), this->radio_button_view, SLOT(click()));
//  QObject::connect(&widget_qgl_viewer->destination_teleport_arrow, SIGNAL(deactivated()), this->radio_button_view, SLOT(click()));

}

PlaneCalibrationUI::~PlaneCalibrationUI()
{
}

//void DSlamPlannerFrame::on_checkbox_draw_directed_edges_stateChanged(int state) {
//  widget_qgl_viewer->draw_directed_edges = ( state == 0 ) ? false : true;
//  widget_qgl_viewer->redraw();
//}

}// namespace
