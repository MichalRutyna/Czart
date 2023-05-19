#ifndef USTAWIENIA
#define USTAWIENIA

class UST
{
public:

    const int SCREEN_WIDTH = 1700;
    const int SCREEN_HEIGHT = 800;

private:
	UST() {}
	UST(const UST&);
public:
	static UST & pobierz_ustawienia(){
		static UST ustawienia;
		return ustawienia;
	}
};

#endif