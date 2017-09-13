#ifndef qt_visualization_GL_LIST_DRAWER_HPP_
#define qt_visualization_GL_LIST_DRAWER_HPP_

#include <GL/glew.h>
#include <GL/glu.h>

#include <Eigen/Dense>

#include <map>
#include <vector>
#include <memory>
#include <mutex>
#include <iostream>

namespace qt_visualization
{

class GLListDrawer
{
public:
  class GLGenList
  {
  public:
    GLGenList(const Eigen::Vector3f& color = Eigen::Vector3f(0.0f, 0.0f, 0.0f))
    {
      updated_ = false;
      gl_list_id_ = -1;
      color_ = color;
    }

    virtual ~GLGenList()
    {
      deleteOldList();
    }

    void setColor(const Eigen::Vector3f& color)
    {
      color_ = color;
    }

    void draw()
    {
      if (updated_)
      {
        deleteOldList();

        gl_list_id_ = ::glGenLists(1);
        glNewList(gl_list_id_, GL_COMPILE);
        {
          update();
        }
        glEndList();
        updated_ = false;
      }
      ::glCallList(gl_list_id_);
    }

  protected:
    virtual void update() = 0;
    void deleteOldList()
    {
      if (gl_list_id_ > 0)
      {
        glDeleteLists(gl_list_id_, 1);
      }
    }

    bool updated_;
    int gl_list_id_;
    Eigen::Vector3f color_;
  };

  class Lines : public GLGenList
  {
  public:
    Lines(const Eigen::Vector3f& color = Eigen::Vector3f(0.0f, 0.0f, 0.0f), const float& line_width = 1.0f) :
        GLGenList(color)
    {
      line_width_ = line_width;
    }

    Lines(const float& line_width)
    {
      line_width_ = line_width;
    }

    void setLineWidth(const float& line_width)
    {
      line_width_ = line_width;
    }

    void add(const float& point1_x, const float& point1_y, const float& point1_z, const float& point2_x,
             const float& point2_y, const float& point2_z)
    {
      line_coordinates_.push_back(point1_x);
      line_coordinates_.push_back(point1_y);
      line_coordinates_.push_back(point1_z);

      line_coordinates_.push_back(point2_x);
      line_coordinates_.push_back(point2_y);
      line_coordinates_.push_back(point2_z);
      updated_ = true;
    }

  protected:
    virtual void update() override
    {
      glColor3f(color_.x(), color_.y(), color_.z());
      glLineWidth(line_width_);
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(3, GL_FLOAT, 0, line_coordinates_.data());
      glDrawArrays(GL_LINES, 0, line_coordinates_.size() / 3);
      glDisableClientState(GL_VERTEX_ARRAY);
    }

    float line_width_;
    std::vector<float> line_coordinates_;
  };

  class Points : public GLGenList
  {
  public:
    Points(const Eigen::Vector3f& color = Eigen::Vector3f(0.0f, 0.0f, 0.0f), const float& size = 1.0f) :
        GLGenList(color)
    {
      size_ = size;
    }

    Points(const float& size)
    {
      size_ = size;
    }

    void setSize(const float& size)
    {
      size_ = size;
    }

    void add(const float& x, const float& y, const float& z)
    {
      point_coordinates_.push_back(x);
      point_coordinates_.push_back(y);
      point_coordinates_.push_back(z);
      updated_ = true;
    }

  protected:
    virtual void update() override
    {
      glColor3f(color_.x(), color_.y(), color_.z());
      glPointSize(size_);
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(3, GL_FLOAT, 0, point_coordinates_.data());
      glDrawArrays(GL_POINTS, 0, point_coordinates_.size() / 3);
      glDisableClientState(GL_VERTEX_ARRAY);
    }

    float size_;
    std::vector<float> point_coordinates_;
  };

  class Polygons : public GLGenList
  {
  public:
    Polygons(const Eigen::Vector3f& color = Eigen::Vector3f(0.0f, 0.0f, 0.0f)) :
        GLGenList(color)
    {
    }

    void addPoints(const Eigen::Vector3f& point1, const Eigen::Vector3f& point2, const Eigen::Vector3f& point3)
    {
      addPoint(point1.x(), point1.y(), point1.z());
      addPoint(point2.x(), point2.y(), point2.z());
      addPoint(point3.x(), point3.y(), point3.z());
      updated_ = true;
    }

  protected:
    virtual void update() override
    {
      glColor3f(color_.x(), color_.y(), color_.z());
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(3, GL_FLOAT, 0, point_coordinates_.data());
      glDrawArrays(GL_POLYGON, 0, point_coordinates_.size() / 3);
      glDisableClientState(GL_VERTEX_ARRAY);
    }

    void addPoint(const float& x, const float& y, const float& z)
    {
      point_coordinates_.push_back(x);
      point_coordinates_.push_back(y);
      point_coordinates_.push_back(z);
    }

    std::vector<float> point_coordinates_;
  };

  GLListDrawer();
  virtual ~GLListDrawer()
  {
  }

  virtual void setLines(const Eigen::Vector3f& color = Eigen::Vector3f(0.0f, 0.0f, 0.0f), const std::string& id = "");
  virtual void setLineWidth(const float& line_width = 1.0f, const std::string& id = "");

  virtual void addLine(const Eigen::Vector3f& point1, const Eigen::Vector3f& point2, const std::string& id = "");
  virtual void addLine(const Eigen::Matrix<float, 6, 1>& line, const std::string& id = "");
  virtual void addLine(const float& point1_x, const float& point1_y, const float& point1_z, const float& point2_x,
                       const float& point2_y, const float& point2_z, const std::string& id = "");

  virtual void clearLines(const std::string& id = "");
  virtual void clearAllLines();

  virtual void setPoints(const Eigen::Vector3f& color = Eigen::Vector3f(0.0f, 0.0f, 0.0f), const std::string& id = "");
  virtual void setPointSize(const float& size = 1.0f, const std::string& id = "");

  virtual void addPoint(const Eigen::Vector3f& point, const std::string& id = "");
  virtual void addPoint(const float& x, const float& y, const float& z, const std::string& id = "");

  virtual void setPolygons(const Eigen::Vector3f& color = Eigen::Vector3f(0.0f, 0.0f, 0.0f),
                           const std::string& id = "");
  virtual void addPolygon(const Eigen::Vector3f& point1, const Eigen::Vector3f& point2, const Eigen::Vector3f& point3,
                          const std::string& id = "");

  virtual void clearAll();

  virtual void draw();

protected:
  virtual void addLine_(const float& point1_x, const float& point1_y, const float& point1_z, const float& point2_x,
                        const float& point2_y, const float& point2_z, const std::string& id = "");

  std::mutex mutex_;
  std::map<std::string, Lines> lines_;
  std::map<std::string, Points> points_;
  std::map<std::string, Polygons> polygons_;
};
typedef std::shared_ptr<GLListDrawer> GLListDrawerPtr;

} //  namespace

#endif
