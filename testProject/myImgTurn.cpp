#include "myImgTurn.h"
#include <math.h>

int ImgTurn::turn(double angle)
{
	ImgTurn out;
	out.m_height = m_height;
	out.m_width = m_width;
	out.bufferLen = stride(m_width) * m_height;
	out.m_buffer = new uint8_t[out.bufferLen];

	for (int y = 0; y < m_height; ++y) {
		for (int x = 0; x < m_width; ++x) {
			int dst = computeArrPos(x, y);
			int src = computeArrPos(x, y + x * tan(angle));
			if (dst > out.bufferLen) break;
			if (src > bufferLen) break;
			out.m_buffer[dst] = m_buffer[src];
			out.m_buffer[dst + 1] = m_buffer[src + 1];
			out.m_buffer[dst + 2] = m_buffer[src + 2];
		}
	}
	out.save("output.bmp");
	return 0;
	
}

size_t ImgTurn::computeArrPos(size_t x, size_t y)
{
	return 3 * x + y * stride(m_width);
}

size_t ImgTurn::stride(size_t w)
{
	return ((3 * w - 1) / 4 + 1) * 4;
}