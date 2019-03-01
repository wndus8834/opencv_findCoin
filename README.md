## opencv_findCoin
### **동전 찾기**

![image](https://user-images.githubusercontent.com/38427658/53637322-2c5af500-3c66-11e9-9cd7-86a30bb8457c.png)

(a) 원 영상
    
* 추출하고자 하는 원이 있는 이미지 사진을 불러옵니다.

(b) 이진화 영상
```cpp
//컬러인 경우 흑백으로 변환한다
	if (pDoc->m_srcImage.channels() == 3)
		cvtColor(pDoc->m_srcImage, srcImage, CV_BGR2GRAY);
	else
		srcImage = pDoc->m_srcImage;

	vector<Vec3f> circles;
	HoughCircles(srcImage, circles, CV_HOUGH_GRADIENT, 1, 1, 200, 100, 1, 100);
	vector<Vec3f>::const_iterator itc = circles.begin();
	while (itc != circles.end()) {
		rectangle(srcImage, Point((*itc)[0] - (*itc)[2], (*itc)[1] + (*itc)[2]),
			Point((*itc)[0] + (*itc)[2], (*itc)[1] - (*itc)[2]), Scalar(0, 255, 255), 8, 0);
		++itc;
	}
```
* 이진화는 가장 간단한 세그멘테이션(segmentation) 방법이다.  세그멘테이션이란 이미지를 분할하여 원하는 부분 혹은 물체를 검출하는데 많이 사용되는 기법이다.
* 이진화는 원본 영상을 그레이 영상으로 변환한 후,  threshold값을 이용하여 배경과 물체를 분리해내는 것이다. 

(c) 추출된 영상
```cpp
	//라벨링 된 이미지에 각각 직사각형으로 둘러싸기 
	for (int j = 1; j < numOfLabels; j++) {
		int area = stats.at<int>(j, CC_STAT_AREA);
		int left = stats.at<int>(j, CC_STAT_LEFT);
		int top = stats.at<int>(j, CC_STAT_TOP);
		int width = stats.at<int>(j, CC_STAT_WIDTH);
		int height = stats.at<int>(j, CC_STAT_HEIGHT);

		rectangle(img_binary, Point(left, top), Point(left + width, top + height),
			Scalar(255, 255, 0), 1);
	}
```
* 검출된 원 주변에 직사각형으로 둘러줌으로써 검출 결과를 나타낸다.