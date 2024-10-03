#include "Framebuffer.h"
#include "Renderer.h"

//setup
Framebuffer::Framebuffer(const Renderer& renderer, int width, int height)
{
	m_width = width;
	m_height = height;
	m_pitch = width * sizeof(color_t);

	m_texture = SDL_CreateTexture(renderer.m_renderer,SDL_PIXELFORMAT_RGBA32,SDL_TEXTUREACCESS_STREAMING,width,height);
	if (!m_texture) {
		std::cerr << "Error creating Texture: " << SDL_GetError() << std::endl;
	}
	m_buffer.resize(m_width * m_height);
}

Framebuffer::~Framebuffer()
{
	SDL_DestroyTexture(m_texture);
}

void Framebuffer::Update()
{
	SDL_UpdateTexture(m_texture, NULL, m_buffer.data(), m_pitch);
}

void Framebuffer::Clear(const color_t& color)
{
	std::fill(m_buffer.begin(),m_buffer.end(),color);
}

//shape draws
void Framebuffer::DrawPoint(int x, int y, const color_t& color)
{
	if (x < 0 || x >= m_width)  return;
	if (y < 0 || y >= m_height) return;

	m_buffer[x + (y * m_width)] = color;
}

void Framebuffer::DrawRect(int x, int y, int w, int h, const color_t& color)
{
	//Maple's Way
	if (x + w < 0 || x >= m_width || y + h < 0 || y >= m_height) return;

	int x1 = std::max(x, 0);
	int x2 = std::min(x + w, m_width);
	int y1 = std::max(y, 0);
	int y2 = std::min(y + h, m_height);

	for (int sy = y1; sy < y2; sy++) {
		int index = x1 + sy * m_width;
		std::fill(m_buffer.begin() + index, m_buffer.begin() + (index + x2 - x1),color);
	}

	// ** My way ** //
	//for (int i = 0; i < h; i++) {
	//	if (i + y >= m_height || i + y < 0) continue;
	//	for (int j = 0; j < w; j++) {
	//		if (j + x >= m_width || j + x < 0) continue;
	//
	//		//draw rect
	//		DrawPoint(x + j, y + i,color);
	//	}
	//}

}

void Framebuffer::DrawLineSlope(int x1, int y1, int x2, int y2, const color_t& color)
{
	//y = mx + b

	int dx = x2 - x1; //run
	int dy = y2 - y1; //rise
	
	if (dx == 0) {
		if (y1 > y2) std::swap(y1, y2);
		for (int y = y1; y < y2; y++) {
			m_buffer[x1 + y * m_width] = color;
		}
	}
	else {
		float m = dy / (float)dx; // rise over run
		float b = y1 - (m * x1);

		if (std::abs(dx) > std::abs(dy)) {
			for (int x = x1; x <= x2; x++) {
				int y = (int)round((m * x) + b);
				m_buffer[x + y * m_width] = color;
			}
		}
		else {
			for (int y = y1; y < y2; y++) {
				int x = (int)round((y - b) / m);
				m_buffer[x + y * m_width] = color;
			}
		}
	}
}

void Framebuffer::DrawLine(int x1, int y1, int x2, int y2, const color_t& color)
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	bool steep = (std::abs(dy) > std::abs(dx));
	if (steep) {
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	dx = x2 - x1;
	dy = std::abs(y2 - y1);

	int error = dx / 2;
	int ystep = (y1 < y2) ? 1 : -1;


	int y = y1;
	for (int x = x1; x < x2; x++) {
		steep ? DrawPoint(y, x, color) : DrawPoint(x, y, color);
		error -= dy;
		if (error < 0) {
			y += ystep;
			error += dx;
		}
	}
}

void Framebuffer::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color)
{
	if (x1 > m_width || y1 > m_height) return;
	if (x2 > m_width || y2 > m_height) return;
	if (x3 > m_width || y3 > m_height) return;

	DrawLine(x1, y1, x2, y2, color);
	DrawLine(x2, y2, x3, y3, color);
	DrawLine(x3, y3, x1, y1, color);
}

void Framebuffer::DrawCircle(int xc, int yc, int radius, const color_t& color)
{

}