#ifndef qt_visualization_PLANE_CALIBRATION_FRAME_HPP_
#define qt_visualization_PLANE_CALIBRATION_FRAME_HPP_

// WARNING : other headers should not include this header because the
// ui generated header will not get included in an install.
#include <QFrame>
#include "ui_plane_calibration.h"

namespace qt_visualization
{

class PlaneCalibrationUI : public QMainWindow, public Ui::PlaneCalibration
{
  Q_OBJECT
public:
  PlaneCalibrationUI();
  virtual ~PlaneCalibrationUI();

  void closeEvent(QCloseEvent *event); // Overloaded function

  void readSettings(); // Load up qt program settings at startup

public Q_SLOTS:
  void writeSettings();
  // Save qt program settings when closing
//  void on_checkbox_draw_camera_frames_stateChanged(int state);
//  void on_checkbox_draw_base_frames_stateChanged(int state);
//  void on_checkbox_draw_frame_ids_stateChanged(int state);
//  void on_checkbox_draw_directed_edges_stateChanged(int state);
//  void on_checkbox_draw_directed_path_stateChanged(int state);
//  void on_checkbox_draw_window_subpath_stateChanged(int state);
//  void on_checkbox_draw_window_grid_stateChanged(int state);
//
//  void on_radio_button_total_cost_clicked();
//  void on_radio_button_graph_costs_clicked();
//  void on_radio_button_obstacle_costs_clicked();
//  void on_radio_button_no_costs_clicked();
//  void on_radio_button_view_clicked();
//  void on_radio_button_set_origin_clicked();
//  void on_radio_button_set_destination_clicked();

};

} // namespace

#endif
