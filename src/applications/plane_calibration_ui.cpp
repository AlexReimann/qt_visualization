
#include <qt_visualization/plane_calibration_ui.hpp>

namespace qt_visualization
{

PlaneCalibrationUI::PlaneCalibrationUI()
{
  setupUi(this);
  setWindowTitle("Graph Viewer");
//  QObject::connect(QApplication::instance(), SIGNAL(aboutToQuit()), this, SLOT(writeSettings()));
//  QObject::connect(&widget_qgl_viewer->origin_teleport_arrow, SIGNAL(deactivated()), this->radio_button_view, SLOT(click()));
//  QObject::connect(&widget_qgl_viewer->destination_teleport_arrow, SIGNAL(deactivated()), this->radio_button_view, SLOT(click()));
  // fill in the help tabs
  readSettings();
}

PlaneCalibrationUI::~PlaneCalibrationUI() {
}

void PlaneCalibrationUI::closeEvent(QCloseEvent *event)
{
  writeSettings();
//  QMainWindow::closeEvent(event);
}

void PlaneCalibrationUI::readSettings() {
//  QSettings settings("Yujin Robot", "DSlam Viewer");
//  restoreGeometry(settings.value("geometry").toByteArray());
  QRect rect = geometry();
//  restoreState(settings.value("window_state").toByteArray());
//  widget_qgl_viewer->draw_camera_frames = settings.value("draw_camera_frames", false).toBool();
//  checkbox_draw_camera_frames->setChecked(widget_qgl_viewer->draw_camera_frames);
//  widget_qgl_viewer->draw_base_frames = settings.value("draw_base_frames", false).toBool();
//  checkbox_draw_base_frames->setChecked(widget_qgl_viewer->draw_base_frames);
//  widget_qgl_viewer->draw_frame_ids = settings.value("draw_frame_ids", false).toBool();
//  checkbox_draw_frame_ids->setChecked(widget_qgl_viewer->draw_frame_ids);
//  widget_qgl_viewer->draw_directed_edges = settings.value("draw_directed_edges", false).toBool();
//  checkbox_draw_directed_edges->setChecked(widget_qgl_viewer->draw_directed_edges);
//  widget_qgl_viewer->draw_directed_path = settings.value("draw_directed_path", false).toBool();
//  checkbox_draw_directed_path->setChecked(widget_qgl_viewer->draw_directed_path);
//  widget_qgl_viewer->draw_window_subpath = settings.value("draw_window_subpath", false).toBool();
//  checkbox_draw_window_subpath->setChecked(widget_qgl_viewer->draw_window_subpath);
//  widget_qgl_viewer->draw_window_grid = settings.value("draw_window_grid", false).toBool();
//  checkbox_draw_window_grid->setChecked(widget_qgl_viewer->draw_window_grid);
//  dslam_tab_widget->setCurrentIndex(settings.value("current_tab").toInt());
//  splitter_main_layout->restoreState(settings.value("splitter_main_layout_sizes").toByteArray());
//  splitter_charts->restoreState(settings.value("splitter_charts_sizes").toByteArray());
}

void PlaneCalibrationUI::writeSettings() {
//  QSettings settings("Yujin Robot", "DSlam Viewer");
//  settings.setValue("geometry", saveGeometry());
//  //settings.setValue("window_state", saveState());
//  settings.setValue("draw_camera_frames",QVariant(checkbox_draw_camera_frames->isChecked()));
//  settings.setValue("draw_base_frames",QVariant(checkbox_draw_base_frames->isChecked()));
//  settings.setValue("draw_frame_ids",QVariant(checkbox_draw_frame_ids->isChecked()));
//  settings.setValue("draw_directed_edges",QVariant(checkbox_draw_directed_edges->isChecked()));
//  settings.setValue("draw_directed_path",QVariant(checkbox_draw_directed_path->isChecked()));
//  settings.setValue("draw_window_subpath",QVariant(checkbox_draw_window_subpath->isChecked()));
//  settings.setValue("draw_window_grid",QVariant(checkbox_draw_window_grid->isChecked()));
//  settings.setValue("current_tab",QVariant(dslam_tab_widget->currentIndex()));
//  settings.setValue("splitter_main_layout_sizes", splitter_main_layout->saveState());
}

//void DSlamPlannerFrame::on_checkbox_draw_directed_edges_stateChanged(int state) {
//  widget_qgl_viewer->draw_directed_edges = ( state == 0 ) ? false : true;
//  widget_qgl_viewer->redraw();
//}


}  // namespace
