#include <Windows.h>
#include <vector>
std::vector<int> Get_PixelColor(int X, int Y) noexcept//Get screen pixel color
{
	static HDC Screen_HDC = GetWindowDC(NULL);
	const COLORREF Pixel = GetPixel(Screen_HDC, X, Y);
	return { GetRValue(Pixel), GetGValue(Pixel), GetBValue(Pixel) };//[0]==Red  [1]==Green  [2]==Blue
}
int main() noexcept//main thread
{
	system("cls");//clear console text
	system("title Triggerbot in any game");//console title
	printf("Github: https://github.com/Coslly/Unusual-Triggerbot.git\n\n");//Github URL
	while (true)//Loop
	{
		const std::vector<int> ScreenResolution = { GetSystemMetrics(SM_CXSCREEN) ,GetSystemMetrics(SM_CYSCREEN) };//Get system monitor pixels
		const auto New_PixelColor = Get_PixelColor(ScreenResolution[0] / 2 + 1, ScreenResolution[1] / 2 + 1);//Read the center position of the screen
		static auto Old_PixelColor = New_PixelColor;//initialization
		if (GetAsyncKeyState(VK_XBUTTON1) & 0x8000)//trigger button
		{
			const auto ColorGap = 50;//To deal with shadow changes(in game)
			if (abs(New_PixelColor[0] - Old_PixelColor[0]) >= ColorGap || abs(New_PixelColor[1] - Old_PixelColor[1]) >= ColorGap || abs(New_PixelColor[2] - Old_PixelColor[2]) >= ColorGap)//check color
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//Shoot!!!
				Sleep(1);//Give the game program time to react
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				Old_PixelColor = New_PixelColor;//refresh
				Beep(100, 50);//return sound
			}
		}
		else Old_PixelColor = New_PixelColor;//Reset
		Sleep(1);//Low down CPU useage
	}
}