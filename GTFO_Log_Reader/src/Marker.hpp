#pragma once

#include <string>
#include <filesystem>

#include <opencv2/opencv.hpp>
#include "JsonManager.hpp"

using namespace cv;

class Marker {
private:
	static std::string GetImagePath(std::string expedition, int zone) {
		return "MAPS\\" + expedition.substr(0, 2) + "\\" + expedition.substr(2, 2) + "\\Zone_" + std::to_string(zone) + ".jpg";
	}

public:
	static bool MarkItem(std::string expedition, int zone, int index) {
		std::string filePath = GetImagePath(expedition, zone);
		if (!std::filesystem::exists(filePath))
			return false;
		
		Position pos = JsonManager::GetPosition(expedition, zone, index);
		if (pos.x == -1)
			return false;

		Mat image = imread(filePath);
		Point point(pos.x, pos.y);

		// circle
		int radius = 40;
		circle(image, point, radius, Scalar(0, 255, 0), 2, LINE_AA);
		
		// index
		int fontFace = FONT_HERSHEY_SIMPLEX;
		Point offset(0, radius / -2 - 20);
		Point textPoint = point + offset;
		putText(image, std::to_string(index), textPoint, FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2, LINE_AA);

		std::string savePath = "MAP\\Zone_" + std::to_string(zone) + "_" + std::to_string(index) + ".jpg";
		imwrite(savePath, image);
		return true;
	}
	static bool MarkKeys(std::string expedition, std::vector<KEY> keys) {
		bool marked = false;
		for (int i = 0; i < keys.size(); i++) {
			std::string filePath = GetImagePath(expedition, keys[i].zone);
			if (!std::filesystem::exists(filePath))
				break;

			Position pos = JsonManager::GetPosition(expedition, keys[i].zone, keys[i].index);
			if (pos.x == -1)
				break;

			Mat image = imread(filePath);
			Point point(pos.x, pos.y);

			// circle
			int radius = 40;
			circle(image, point, radius, Scalar(0, 255, 0), 2, LINE_AA);

			// index
			Point offset(0, radius / -2 - 20);
			Point textPoint = point + offset;
			putText(image, std::to_string(keys[i].index), textPoint, FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2, LINE_AA);

			std::string savePath = "MAP\\Zone_" + std::to_string(keys[i].zone) + "_" + std::to_string(keys[i].index) + ".jpg";
			imwrite(savePath, image);
			marked = true;
		}
		return marked;
	}
};









