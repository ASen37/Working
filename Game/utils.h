#pragma once
#include <graphics.h>
#pragma comment (lib, "MSIMG32.LIB")

inline void flip_image(IMAGE* img, IMAGE* dst) {
	int w = img->getwidth();
	int h = img->getheight();
	Resize(dst, w, h);
	DWORD* img_buffer = GetImageBuffer(img);
	DWORD* dst_buffer = GetImageBuffer(dst);

	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			int id_img = y * w + x;
			int id_dst = y * w + (w - x - 1);
			dst_buffer[id_dst] = img_buffer[id_img];
		}
	}
}

inline void flip_atlas(Atlas& src, Atlas& dst)
{
	dst.clear();
	for (int i = 0; i < src.get_size(); i++) {
		IMAGE img_dst;
		flip_image(src.get_image(i), &img_dst);
		dst.add_img(img_dst);
	}
}

inline void putimage_alpha(int dst_x, int dst_y, IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, 
		w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA }
	);
}

inline int get_dir(int code) {
	if (code == 0x8) return 1;
	if (code == 0x4) return -1;
	return 0;
}

// 切换到中文键盘的拼音模式
inline void switch_keyboard()
{
	// 模拟按键CTRL + SPACE 切换键盘到英文模式
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event(VK_SPACE, 0, 0, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
}
