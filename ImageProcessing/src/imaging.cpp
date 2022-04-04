#include "include/imaging.h"

using namespace std;

/// <summary>
/// Read the image.
/// </summary>
Mat Imaging::read(char const* path) {
    return imread(path, IMREAD_COLOR);
}

/// <summary>
/// Convert the image to grayscale.
/// </summary>
/// <param name="img">Img to convert</param>
Mat Imaging::convertTogray(Mat img) {
    cvtColor(img, img, COLOR_BGR2GRAY);
    return img;
}

/// <summary>
/// Convert the image from BGR to RGB color model.
/// </summary>
/// <param name="img">Img to convert.</param>
/// <returns></returns>
Mat Imaging::convertToRGB(Mat img) {
    cvtColor(img, img, COLOR_BGR2RGB);
    return img;
}

/// <summary>
/// Resize the image.
/// </summary>
/// <param name="img">Image to resize</param>
/// <param name="target">Target size of the new image.</param>
Mat Imaging::resize(Mat img, int target) {

    int width = img.cols,
        height = img.rows;

    cv::Mat square = cv::Mat::zeros(target, target, img.type());

    int max_dim = (width >= height) ? width : height;
    float scale = ((float)target) / max_dim;

    cv::Rect roi;
    if (width >= height)
    {
        roi.width = target;
        roi.x = 0;
        roi.height = height * scale;
        roi.y = (target - roi.height) / 2;
    }
    else
    {
        roi.height = target;
        roi.y = 0;
        roi.width = width * scale;
        roi.x = (target - roi.width) / 2;
    }

    cv::resize(img, square(roi), roi.size());
    return square;
}

/// <summary>
/// Show the image.
/// </summary>
/// <param name="img">Img to show</param>
/// <param name="windowName">Window name</param>
void Imaging::show(Mat img, string windowName) {

    if (img.empty())
    {
        std::cout << "Could not read the image! " << std::endl;
    }

    try {
        imshow(windowName, img);
        waitKey(0);
    }
    catch (const char* e) {
        cerr << e << endl;
    }
}

/// <summary>
/// Blurring the imahe.
/// </summary>
/// <param name="img">Imahe to blur.</param>
/// <returns></returns>
Mat Imaging::blur(Mat img, Size size) {
    blur(img, img, size);
    return img;
}

/// <summary>
/// Apply the Canny operator.
/// </summary>
/// <param name="img">Input image</param>
Mat Imaging::canny(Mat img) {

    int lowThreshold = 0;
    const int max_lowThreshold = 100;
    const int ratio = 3;
    const int kernel_size = 3;

    Canny(img, img, lowThreshold, lowThreshold * ratio, kernel_size);
    return img;
}
