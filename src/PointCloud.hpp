#ifndef __A1_PointCloud_hpp__
#define __A1_PointCloud_hpp__

#include "Common.hpp"
#include "Point.hpp"
#include "DGP/AxisAlignedBox3.hpp"
#include "DGP/Noncopyable.hpp"
#include "DGP/Graphics/RenderSystem.hpp"
#include "PointKDTree.hpp"
#include "DGP/Vector3.hpp"

/** A set of 3D points. */
class PointCloud
{
  private:
    std::vector<Point> points;
    AxisAlignedBox3 bbox;
    int64 nlabels;
    int64 nobjects;

  public:
    /** Default constructor. */
    PointCloud() {}

    /** Construct from a list of points. */
    PointCloud(std::vector<Point> const & points_);

    /** Construct from a list of positions and normals. */
    PointCloud(std::vector<Vector3> const & positions, std::vector<Vector3> const & normals);

    /** Get the number of points. */
    long numPoints() const { return (long)points.size(); }

    /** Check if the point cloud is empty. */
    bool isEmpty() const { return points.empty(); }

    /** Reset the point cloud to an empty state. */
    void clear() { points.clear(); bbox.setNull(); }

    /** Get the list of points. */
    std::vector<Point> const & getPoints() const { return points; }

    /** Get the i'th point. */
    Point const & getPoint(long i) const { return points[(size_t)i]; }

    /** Add a point to the point cloud. */
    void addPoint(Point const & p) { points.push_back(p); bbox.merge(p.getPosition()); }

    /** Add a point, specified by its position and normal, to the point cloud. */
    void addPoint(Vector3 const & p, Vector3 const & n) { points.push_back(Point(p, n)); bbox.merge(p); }

    /** Get the bounding box of the point cloud. */
    AxisAlignedBox3 const & getAABB() const { return bbox; }

    /** Load the point cloud from a disk file. */
    bool load(std::string const & path);

    /** Save the point cloud to a disk file. */
    bool save(std::string const & path) const;
    bool saveFeatures(std::string const & path) const;

    /** Draw the point cloud using a render-system. */
    void draw(Graphics::RenderSystem & rs, Real normal_len = -1, ColorRGBA const & color = ColorRGB(0.5, 0.5, 0.5)) const;

    /** TODO: Estimate the normals of the points. If any normals exist, they will be ignored and recomputed. */
    void estimateNormals();

    /**
     * TODO: Adaptively resample the point cloud to reduce the number of points in smooth areas. Don't introduce any new points.
     */
    void adaptiveDownsample();

    bool loadISM_BIN(std::string const & path_);
    bool extract_objects(std::string const & out_dir_path);
    bool extract_labels(std::string const & out_dir_path);

  private:
    /** Recompute the bounding box. */
    void recomputeAABB();

}; // class PointCloud

#endif
