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
};

} // namespace

#endif
