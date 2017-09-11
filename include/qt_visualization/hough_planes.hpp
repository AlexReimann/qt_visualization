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
  Eigen::MatrixXd getVotes();

protected:
  typedef Eigen::Matrix<float, 6, 1> Line;

  void vote(const int& point_index, const float& angle);

  Line center_line_;
  std::vector<Eigen::Vector3f> data_points_;

  double step_size_;
  double max_angle_;
  double angle_bin_size_;

  std::string name_all_;
  std::string name_selected_;
  GLListDrawerPtr list_drawer_;

  Eigen::MatrixXd votes_;
};

}  // namespace

#endif
