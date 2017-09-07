#ifndef qt_visualization_HOUGH_PLANES_HPP_
#define qt_visualization_HOUGH_PLANES_HPP_

#include "qt_visualization/gl_list_drawer.hpp"

#include <Eigen/Dense>
#include <string>
#include <vector>

namespace qt_visualization
{

class HoughPlanes
{
public:
  HoughPlanes(GLListDrawerPtr list_drawer);

  void setup();
  void run();

protected:

  typedef Eigen::Matrix<float, 6, 1> Line;

  Line center_line_;
  std::vector<Eigen::Vector3f> data_points_;

  double step_size_;
  double max_angle_;

  std::string name_all_;
  std::string name_selected_;
  GLListDrawerPtr list_drawer_;
};

}  // namespace

#endif
