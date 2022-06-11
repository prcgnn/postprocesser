 // First, include ros library
#include <ros/ros.h>

 // Include then pcl library required
    #include <pcl_conversions/pcl_conversions.h>
    #include <pcl/point_cloud.h>
    #include <pcl/point_types.h>
    #include <pcl/filters/voxel_grid.h>
    #include <pcl/filters/statistical_outlier_removal.h>
    #include <pcl/filters/statistical_outlier_removal.h>
    #include <pcl/io/pcd_io.h>

 // Include PointCloud2 message
 #include <sensor_msgs/PointCloud2.h>

 // Topics (corrected, needs to be checked)
 static const std::string IMAGE_TOPIC = "/d400/depth/color/points";
 static const std::string PUBLISH_TOPIC = "/pointcloudfiltered";

 // ROS Publisher
 ros::Publisher pub;

 void cloud_cb(const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
 {

     // Container for original & filtered data
     pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2;
     pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
     pcl::PCLPointCloud2 cloud_filtered;

     // Convert to PCL data type
     pcl_conversions::toPCL(*cloud_msg, *cloud);
     //filtering with StatisticalOutlierRemoval
     pcl::StatisticalOutlierRemoval<pcl::PCLPointCloud2> sor;
     sor.setInputCloud(cloudPtr);
     sor.setMeanK(9);
     sor.setStddevMulThresh(1.0);
     sor.filter(cloud_filtered);

     // Convert to ROS data type
     sensor_msgs::PointCloud2 output;
     pcl_conversions::moveFromPCL(cloud_filtered, output);

     // Publish the data
     pub.publish (output);
 }

 int main (int argc, char** argv)
 {
     // Initialize the ROS Node ""
     ros::init (argc, argv, "subscriber_filter_republisher");
     ros::NodeHandle nh;
     //std::cout << "Type 0 for Voxel grid filtering, 1 for Statistical Outlier Removal: ";
     //std::cin >> i;
     //std::cout << "You have chosen: " << i;
     // Print "Hello" message with node name to the terminal and ROS log file
     ROS_INFO_STREAM("Hello from ROS Node: " << ros::this_node::getName());

     // Create a ROS Subscriber to IMAGE_TOPIC with a queue_size of 1 and a callback function to cloud_cb
     ros::Subscriber sub = nh.subscribe(IMAGE_TOPIC, 1, cloud_cb);

     // Create a ROS publisher to PUBLISH_TOPIC with a queue_size of 1
     pub = nh.advertise<sensor_msgs::PointCloud2>(PUBLISH_TOPIC, 1);

     // Spin
     ros::spin();

     // Success
     return 0;
 }