#pragma once

	template<typename T>
	inline T Lerp(T a, T b, float t) { return static_cast<T>(a + (t * (b - a))); };

	inline void QuadraticPoint(int x1, int y1, int x2, int y2, int x3, int y3,float t, int& x, int& y) {
		float one_minus_t = 1 - t;
		float a1 = one_minus_t * one_minus_t; // std::pow(one_minus_t1,2)
		float b1 = 2 * one_minus_t * t;
		float c1 = t * t;


		x = (int)(a1 * x1 + b1 * x2 + c1 * x3);
		y = (int)(a1 * y1 + b1 * y2 + c1 * y3);
	}

	inline void CubicPoint(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, float t, int& x, int& y) {
		float one_minus_t = 1 - t;
		float a = one_minus_t * (one_minus_t * one_minus_t); // std::pow(one_minus_t1,2)
		float b = 3 * (one_minus_t * one_minus_t) * t;
		float c = 3 * one_minus_t * (t * t);
		float d = t * t * t;


		x = (int)(a * x1 + b * x2 + c * x3 + d * x4);
		y = (int)(a * y1 + b * y2 + c * y3 + d * y4);
	}
