#include "qt_visualization/hough_planes.hpp"
#include <plane_calibration/plane_to_depth_image.hpp>
#include <iostream>

namespace qt_visualization
{

HoughPlanes::HoughPlanes(GLListDrawerPtr list_drawer)
{
  step_size_ = 0.01;
  angle_bin_size_ = 0.00872665;
  max_angle_ = M_PI; //0.174533 * 3;
  ninety_degree_threshold_scaler_ = 0.15;

  list_drawer_ = list_drawer;

  name_all_ = "all_point_to_center";
  name_plane_ = "plane";
  name_selected_ = "selected_point_to_center";
  name_points_ = "points";
  name_perpendicular_ = "perpendicular";

  px_ = 0.0;
  py_ = 0.0;

//  srand((unsigned int) time(0));
}

void HoughPlanes::updatePx(const int& slider_value)
{
  double ratio = slider_value / 99.0;
  px_ = (ratio * 2 * 3.1415) - 3.1415;
  setup(px_, py_);
  run();
}

void HoughPlanes::updatePy(const int& slider_value)
{
  double ratio = slider_value / 99.0;
  py_ = (ratio * 2 * 3.1415) - 3.1415;
  setup(px_, py_);
  run();
}

void HoughPlanes::setup(double px, double py)
{
  center_line_ << -5, -5, -5, 5, 5, 5;

  Eigen::Vector3f center_vector = center_line_.bottomRows(3) - center_line_.topRows(3);

  double center_line_length = (center_vector).norm();
  int steps = center_line_length / step_size_;
  int angle_steps = max_angle_ * 2.0 / angle_bin_size_;

  std::cout << "steps: " << steps << std::endl;
  std::cout << "angle_steps: " << angle_steps << std::endl;
  std::cout << "angle_steps: " << max_angle_ * 2.0 / angle_bin_size_ << std::endl;

  votes_ = Eigen::MatrixXd::Zero(angle_steps, steps);
  list_drawer_->clearAll();
  data_points_.clear();

  std::cout << "size: " << votes_.cols() << ", " << votes_.rows() << std::endl;

  Eigen::Vector3f plane_point(1, 2, 1);

  Eigen::AngleAxisf rotation;
  rotation = Eigen::AngleAxisf(px, Eigen::Vector3f::UnitX()) * Eigen::AngleAxisf(py, Eigen::Vector3f::UnitY())
      * Eigen::AngleAxisf(0.0, Eigen::Vector3f::UnitZ());

  Eigen::Vector3f plane_normal = rotation * Eigen::Vector3f::UnitZ();

  Eigen::Hyperplane<float, 3> plane(plane_normal, plane_point);

  double plane_half_size = center_line_length * 0.5;
  Eigen::Vector3f plane_point_1 = plane_normal + Eigen::Vector3f(plane_half_size, plane_half_size, 0.0);
  Eigen::Vector3f plane_point_2 = plane_normal + Eigen::Vector3f(plane_half_size, -plane_half_size, 0.0);
  Eigen::Vector3f plane_point_3 = plane_normal + Eigen::Vector3f(-plane_half_size, -plane_half_size, 0.0);
  Eigen::Vector3f plane_point_4 = plane_normal + Eigen::Vector3f(-plane_half_size, plane_half_size, 0.0);

  list_drawer_->addPolygon(plane.projection(plane_point_1), plane.projection(plane_point_2),
                           plane.projection(plane_point_3), name_plane_);
  list_drawer_->addPolygon(plane.projection(plane_point_4), plane.projection(plane_point_4),
                           plane.projection(plane_point_1), name_plane_);
  list_drawer_->setPolygons(Eigen::Vector3f(0, 1.0, 0), name_plane_);

  float d = (plane_point).dot(plane_normal) / center_vector.dot(plane_normal);

//  list_drawer_->addPoint(center_vector * d, "intersection");
//  list_drawer_->setPoints(Eigen::Vector3f(0.0, 0, 1.0), "intersection");
//  list_drawer_->setPointSize(5.0, "intersection");

  int points_count = 100;
  Eigen::Vector3f test_point(1, 2, 1);
  data_points_.push_back(test_point);

  for (int i = 0; i < points_count; ++i)
  {
    Eigen::Vector3f point = Eigen::Vector3f::Random();

    // random is [-1:1]
    point(0) = point(0) + 2;
    point(1) = point(1) + 2;
    point(2) = point(2) + 2;

    Eigen::Vector3f point_on_plane = plane.projection(point) + Eigen::Vector3f::Random() * 0.2;

    data_points_.push_back(point_on_plane);
    list_drawer_->addPoint(point_on_plane, name_points_);

//    std::cout << i << " point: " << point.transpose() << std::endl;
  }

  list_drawer_->setPoints(Eigen::Vector3f(1, 0, 0), "best");
  list_drawer_->setPointSize(4.0, "best");

  list_drawer_->setLines(Eigen::Vector3f(1, 0, 1), name_perpendicular_);
  list_drawer_->setLineWidth(4.0, name_perpendicular_);

  list_drawer_->setPoints(Eigen::Vector3f(1, 1, 1), name_points_);
  list_drawer_->setPointSize(3.0, name_points_);

  list_drawer_->setLines(Eigen::Vector3f(1, 1, 1));
  list_drawer_->setLineWidth(3.0f);
  list_drawer_->addLine(center_line_);

  list_drawer_->setLineWidth(2.0f, name_selected_);
  list_drawer_->setLines(Eigen::Vector3f(1, 0.5, 0), name_all_); // orange
  list_drawer_->setLines(Eigen::Vector3f(0, 0.5, 1), name_selected_); // blue

  std::cout << "--------------- end of setup ---------------" << std::endl;
}

void HoughPlanes::run()
{
  Eigen::Vector3f center_vector = center_line_.bottomRows(3) - center_line_.topRows(3);
  double center_line_length = center_vector.norm();

  std::cout << "center_vector: " << center_vector.transpose() << std::endl;
  std::cout << "center_line_length: " << center_line_length << std::endl;
  center_vector.normalize();

  Eigen::Vector3f center_point = center_line_.topRows(3) + center_vector * step_size_;

  std::cout << "center_vector: " << center_vector.transpose() << std::endl;
  std::cout << "step: " << (center_vector * step_size_).transpose() << std::endl;

  // normalized stays the same
  Eigen::Vector2f center_point_xy_normalized = center_point.topRows(2).normalized();
  std::cout << "center_point: " << center_point.transpose() << std::endl;

  double distance = (center_line_.topRows(3) - center_point).norm();

  std::cout << "distance 0: " << distance << std::endl;
  int center_point_index = 0;
  while (distance < center_line_length)
  {
    // for now quick and dirty
    for (int i = 0; i < data_points_.size(); ++i)
    {
      Eigen::Vector2f vector_to_center_point = center_point.topRows(2) - data_points_[i].topRows(2);

      float scaler = data_points_[i].topRows(2).dot(center_point_xy_normalized);
      Eigen::Vector2f perpendicular_point = scaler * center_point_xy_normalized;

//      list_drawer_->addLine(Eigen::Vector3f(perpendicular_point.x(), perpendicular_point.y(), 0.0f), data_points_[i], name_perpendicular_);

      Eigen::Vector2f vector_to_closest_center_point = perpendicular_point - data_points_[i].topRows(2);

//      float angle = std::acos(vector_to_closest_center_point.normalized().dot(vector_to_center_point.normalized()));

      vector_to_center_point.normalize();
      float angle_other = std::atan2(vector_to_center_point.y(), vector_to_center_point.x());
      vector_to_closest_center_point.normalize();
      float angle_closest = std::atan2(vector_to_closest_center_point.y(), vector_to_closest_center_point.x());

      float angle = constrainAngle(angle_closest - angle_other);
//      std::cout << "------" << std::endl;
//      std::cout << i << " center_point: " << center_point.topRows(2).transpose() << std::endl;
//      std::cout << i << " data: " << data_points_[i].topRows(2).transpose() << std::endl;
//      std::cout << i << " vector_to_closest_center_point: " << vector_to_closest_center_point.transpose() << std::endl;
//      std::cout << i << " vector_to_center_point: " << vector_to_center_point.transpose() << std::endl;
//      std::cout << i << " diff: " << diff.transpose() << std::endl;
//
//      std::cout << "angle: " << angle << std::endl;
//      std::cout << "angle_closest: " << angle_closest << std::endl;

      double abs_angle = std::abs(angle);
      double ninety_degree_in_rad = M_PI_2;
      double upper_threshold = (1.0 + ninety_degree_threshold_scaler_) * ninety_degree_in_rad;
      double lower_threshold = (1.0 - ninety_degree_threshold_scaler_) * ninety_degree_in_rad;
      bool close_to_perpendicular = abs_angle < upper_threshold && abs_angle > lower_threshold;

      if (abs_angle < max_angle_ && !close_to_perpendicular)
      {
//        list_drawer_->addLine(center_point, data_points_[i], name_selected_); // blue

        vote(center_point_index, angle);
      }
      else
      {
//        list_drawer_->addLine(center_point, data_points_[i], name_all_);
      }
    }

    center_point += center_vector * step_size_;
    ++center_point_index;
    distance = (center_line_.topRows(3) - center_point).norm();

//    std::cout << center_point_index << " distance: " << distance << std::endl;
  }
}

void HoughPlanes::vote(const int& point_index, const float& angle)
{
  float offset_angle = angle + max_angle_;

  int angle_index = std::round(offset_angle / angle_bin_size_);
  angle_index = std::min(std::max(angle_index, 0), (int)votes_.rows() - 1);

  if (point_index >= votes_.cols())
  {
    std::cout << "Index too big: " << point_index << std::endl;
//    std::cout << "votes size: " << votes_.rows() << ", " << votes_.cols() << std::endl;
    return;
  }

//  std::cout << "votes size: " << votes_.rows() << ", " << votes_.cols() << std::endl;
//  std::cout << "indices: " << angle_index << ", " << point_index << std::endl;

  votes_(angle_index, point_index) += 1;
}

Eigen::MatrixXd HoughPlanes::getVotes()
{
  Eigen::MatrixXd votes_normalized = votes_ / votes_.maxCoeff();
  return votes_normalized;
}

void HoughPlanes::test(int x, int y)
{
  double angle = x * angle_bin_size_ - max_angle_;

  Eigen::Vector3f center_vector = center_line_.bottomRows(3).normalized();
  Eigen::Vector3f point = center_line_.topRows(3) + center_vector * (step_size_ * y);

//  std::cout << "best: " << x << "," <<  y << std::endl;
//  std::cout << "angle: " << angle << std::endl;
//  std::cout << "diff: " << angle - py_ << std::endl;
//  std::cout << "actual: " << px_ << ", " << py_ << std::endl;
//  std::cout << "point: " << point.transpose() << std::endl;
  list_drawer_->addPoint(point, "best");
}

} // namespace
