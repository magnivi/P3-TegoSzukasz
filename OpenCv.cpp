#include "CMakeProject12.h"
#include <opencv2/opencv.hpp>
#include<string>

using namespace std;
using namespace cv;

/*int main() {
    Mat image = imread("testSample.jpg");
    if (image.empty()) {
        std::cout << "Error loading image!" << std::endl;
        return -1;
    }

    // Define various kernels
    Mat identity = (Mat_<float>(3, 3) <<
        0, 0, 0,
        0, 1, 0,
        0, 0, 0);

    Mat sobelHorizontal = (Mat_<float>(3, 3) <<
        -1, 0, 1,
        -2, 0, 2,
        -1, 0, 1);

    Mat gaussianBlur = (Mat_<float>(3, 3) <<
        1, 2, 1,
        2, 4, 2,
        1, 2, 1) / 16.0f; // Normalize the kernel

    Mat emboss = (Mat_<float>(3, 3) <<
        -2, -1, 0,
        -1, 1, 1,
        0, 1, 2);

    Mat laplacian = (Mat_<float>(3, 3) <<
        0, 1, 0,
        1, -4, 1,
        0, 1, 0);

    Mat boxBlur = (Mat_<float>(3, 3) <<
        1, 1, 1,
        1, 1, 1,
        1, 1, 1) / 9.0f; // Normalize the kernel

    // Add padding to the image to handle border pixels
    int paddingDistance = 1;
    Mat src;
    copyMakeBorder(image, src, paddingDistance, paddingDistance, paddingDistance, paddingDistance, BORDER_REPLICATE);
    Mat out = Mat::zeros(image.rows, image.cols, image.type());

    // Choose the kernel to use here, e.g., K for sharpening
    Mat kernel = sobelHorizontal;

    // Convolution process
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            for (int c = 0; c < image.channels(); c++) {
                float sum = 0.0f;
                for (int h = -1; h <= 1; h++) {
                    for (int w = -1; w <= 1; w++) {
                        int nPixel = src.at<Vec3b>(i + 1 + h, j + 1 + w)[c]; // Value from src at [i+h, j+w, c]
                        float kernel_value = kernel.at<float>(h + 1, w + 1); // Kernel value at [h+1, w+1]
                        sum += nPixel * kernel_value;
                    }
                }
                // Set the result in the out matrix
                out.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(sum);
            }
        }
    }

    imshow("Filtered Image", out);
    waitKey(0);

    return 0;
}*/

int Filter2D(std::string fileName, std::string filter) {
    int paddingDistance = 1;
    Mat src;
    Mat kernel;
    Mat out;

    Mat image = imread(fileName);
    if (image.empty()) {
        std::cout << "Error loading image!" << std::endl;
        return -1;
    }

    copyMakeBorder(image, src, paddingDistance, paddingDistance, paddingDistance, paddingDistance, BORDER_REPLICATE);
    out = Mat::zeros(image.rows, image.cols, image.type());
    

    Mat identity = (Mat_<float>(3, 3) <<
        0, 0, 0,
        0, 1, 0,
        0, 0, 0);

    Mat sobelHorizontal = (Mat_<float>(3, 3) <<
        -1, 0, 1,
        -2, 0, 2,
        -1, 0, 1);

    Mat gaussianBlur = (Mat_<float>(3, 3) <<
        1, 2, 1,
        2, 4, 2,
        1, 2, 1) / 16.0f; 

    Mat emboss = (Mat_<float>(3, 3) <<
        -2, -1, 0,
        -1, 1, 1,
        0, 1, 2);

    Mat laplacian = (Mat_<float>(3, 3) <<
        0, 1, 0,
        1, -4, 1,
        0, 1, 0);

    Mat boxBlur = (Mat_<float>(3, 3) <<
        1, 1, 1,
        1, 1, 1,
        1, 1, 1) / 9.0f; 
    
    if (filter == "identity")  kernel = identity;
    else if (filter == "sobelHorizontal")  kernel = sobelHorizontal;
    else if (filter == "emboss")  kernel = emboss;
    else if (filter == "laplacian") kernel = laplacian;
    else if (filter == "boxBlur")  kernel = boxBlur;
    else return -1;
    
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            for (int c = 0; c < image.channels(); c++) {
                float sum = 0.0f;
                for (int h = -1; h <= 1; h++) {
                    for (int w = -1; w <= 1; w++) {
                        int nPixel = src.at<Vec3b>(i + 1 + h, j + 1 + w)[c]; 
                        float kernel_value = kernel.at<float>(h + 1, w + 1); 
                        sum += nPixel * kernel_value;
                    }
                }
                out.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(sum);
            }
        }
    }
        imshow("Filtered Image", out);
        waitKey(0);
}
int AdvancedFilter2D(const std::string& fileName, const std::vector<std::vector<int>>& wektor) {
    
    size_t rows = wektor.size();
    size_t cols = 0;
    if (rows > 0) {
        cols = wektor[0].size();
    }
    else return -1;
    if (rows != 3 || cols != 3) return -1;

    int paddingDistance = 1;
    Mat src;
    Mat kernel;
    Mat out;

    Mat image = imread(fileName);
    if (image.empty()) {
        std::cout << "Error loading image!" << std::endl;
        return -1;
    }
    kernel = Mat::zeros(3, 3, image.type());
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            kernel.at<float>(i, j) = static_cast<float>(wektor[i][j]);
        }
    }

    copyMakeBorder(image, src, paddingDistance, paddingDistance, paddingDistance, paddingDistance, BORDER_REPLICATE);
    out = Mat::zeros(image.rows, image.cols, image.type());

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            for (int c = 0; c < image.channels(); c++) {
                float sum = 0.0f;
                for (int h = -1; h <= 1; h++) {
                    for (int w = -1; w <= 1; w++) {

                        int nPixel = src.at<Vec3b>(i + 1 + h, j + 1 + w)[c];
                        float kernel_value = kernel.at<float>(h + 1, w + 1);
                        sum += nPixel * kernel_value;
                    }
                }
                out.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(sum);
            }
        }
    }
    imshow("Filtered Image", out);
    waitKey(0);
}
int main()
{
    std::vector<std::vector<int>> wektor = { {0, 0, 0}, {0, 1, 0}, {0, 0, 0} };
    Filter2D("testSample.jpg", "identity");
    //AdvancedFilter2D("testSample.jpg", wektor);
    return 0;
}
