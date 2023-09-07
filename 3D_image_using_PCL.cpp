#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <pcl/common/common_headers.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/pcd_io.h>
#include <pcl/surface/convex_hull.h>
#include <pcl/surface/concave_hull.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/io/vtk_io.h>


int main() {
    // Define a point cloud
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    
    // Populate the point cloud with some sample points
    for (float x = -1.0; x <= 1.0; x += 0.1) {
        for (float y = -1.0; y <= 1.0; y += 0.1) {
            for (float z = -1.0; z <= 1.0; z += 0.1) {
                pcl::PointXYZ point;
                point.x = x;
                point.y = y;
                point.z = z;
                cloud->push_back(point);
            }
        }
    }

    // Create a KdTree object and set the input cloud
    pcl::search::KdTree<pcl::PointXYZ>::Ptr kd_tree(new pcl::search::KdTree<pcl::PointXYZ>);
    kd_tree->setInputCloud(cloud);

    // Define the point for which you want to find the nearest neighbors
    pcl::PointXYZ search_point;
    search_point.x = 0.5;
    search_point.y = 0.0;
    search_point.z = 0.0;

    // Define the number of neighbors to find
    int k = 5;

    // Perform nearest neighbor search
    std::vector<int> indices(k);
    std::vector<float> distances(k);
    kd_tree->nearestKSearch(search_point, k, indices, distances);

    // Print the indices and distances of the nearest neighbors
    std::cout << "Nearest neighbors to point (" << search_point.x << ", " << search_point.y << ", " << search_point.z << "):" << std::endl;
    for (int i = 0; i < k; ++i) {
        int index = indices[i];
        float distance = distances[i];
        pcl::PointXYZ neighbor_point = cloud->points[index];
        std::cout << "Neighbor " << i + 1 << ": Index=" << index << " Distance=" << distance << " Point=(" << neighbor_point.x << ", " << neighbor_point.y << ", " << neighbor_point.z << ")" << std::endl;
    }

    return 0;
}
