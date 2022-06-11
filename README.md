# postprocesser\\
Voxel filtering for processing pointcloud image and publishing (still to be tested) 
The goal of this repo is providing a useful tool to fix the current bugs of RealSense cameras.
It's structured as a single ros pkg, made up of one single node that subscribes itself to PCL topics, filter out and republish. 
Filtering is performed via voxel grid approach that is assumed to remove outlier data. 
Computational time is deemed to be accettable. 
