#include "qt_visualization/hough_planes.hpp"

#include <iostream>

namespace qt_visualization
{

HoughPlanes::HoughPlanes(GLListDrawerPtr list_drawer)
{
  step_size_ = 0.1;
  max_angle_ = 0.174533;
  list_drawer_ = list_drawer;

  name_all_ = "all_point_to_center";
  name_selected_ = "selected_point_to_center";

  srand((unsigned int) time(0));
}

void HoughPlanes::setup()
{
  center_line_ << 0, 0, 0, 5, 5, 5;
  std::cout << "center_line_: " << center_line_.transpose() << std::endl;

  int points_count = 10;

  Eigen::Vector3f test_point(1, 2, 1);
  data_points_.push_back(test_point);

  for (int i = 0; i < points_count; ++i)
  {
    Eigen::Vector3f point = Eigen::Vector3f::Random();

    // random is [-1:1]
    point(0) = point(0) + 2;
    point(1) = point(1) + 2;
    point(2) = point(2) + 2;

    data_points_.push_back(point);

    std::cout << i << " point: " << point.transpose() << std::endl;
  }

  list_drawer_->setLines(Eigen::Vector3f(1, 1, 1)); // orange
  list_drawer_->setLineWidth(2.0f, name_selected_);
  list_drawer_->addLine(center_line_);
  list_drawer_->setLines(Eigen::Vector3f(1, 0.5, 0), name_all_); // orange
  list_drawer_->setLines(Eigen::Vector3f(0, 0.5, 1), name_selected_); // blue

  std::cout << "--------------- end of setup ---------------" << std::endl;
}

void HoughPlanes::run()
{
  Eigen::Vector3f center_vector = center_line_.bottomRows(3).normalized();
  double center_line_length = center_line_.norm();

  std::cout << "center_vector: " << center_vector.transpose() << std::endl;
  std::cout << "center_line_length: " << center_line_length << std::endl;

  Eigen::Vector3f center_point = center_line_.topRows(3) + center_vector * step_size_;

  // normalized stays the same
  Eigen::Vector2f center_point_xy_normalized = center_point.topRows(2).normalized();
  std::cout << "center_point: " << center_point.transpose() << std::endl;

  while (center_point.norm() < center_line_length)
  {
    // for now quick and dirty
    for (int i = 0; i < data_points_.size(); ++i)
    {
      Eigen::Vector2f vector_to_center_point = center_point.topRows(2) - data_points_[i].topRows(2);

      Eigen::Vector2f perpendicular_point = data_points_[i].topRows(2).dot(center_point_xy_normalized) * center_point_xy_normalized;
      Eigen::Vector2f vector_to_closest_center_point = perpendicular_point - data_points_[i].topRows(2);

      Eigen::Vector2f diff = vector_to_closest_center_point - vector_to_center_point;

      float angle_closest = std::atan2(vector_to_closest_center_point.y(), vector_to_closest_center_point.x());
      float angle_other = std::atan2(vector_to_center_point.y(), vector_to_center_point.x());
      float angle = angle_closest - angle_other;
//      std::cout << "------" << std::endl;
//      std::cout << i << " center_point: " << center_point.topRows(2).transpose() << std::endl;
//      std::cout << i << " data: " << data_points_[i].topRows(2).transpose() << std::endl;
//      std::cout << i << " vector_to_closest_center_point: " << vector_to_closest_center_point.transpose() << std::endl;
//      std::cout << i << " vector_to_center_point: " << vector_to_center_point.transpose() << std::endl;
//      std::cout << i << " diff: " << diff.transpose() << std::endl;
//
//      std::cout << "angle: " << angle << std::endl;

      if (std::abs(angle) < max_angle_)
      {
        list_drawer_->addLine(center_point, data_points_[i], name_selected_); // blue
      }
      else
      {
//        list_drawer_->addLine(center_point, data_points_[i], name_all_);
      }
    }

    center_point += center_vector * step_size_;
  }
}

} // namespace
