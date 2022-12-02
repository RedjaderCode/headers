#ifndef REDJADER_H_
#define REDJADER_H_

#include <SDL.h>
#include <SDL_Image.h>
#include <string>
#include <stdio.h>
#include <chrono>
#include <vector>
#include <fstream>
#define log(x) std::cout << x

int printf(const char * str, ...);

#if _WIN32_WINNT
    #if _WIN32_WINNT_WIN10
        #ifdef _WIN32_WINNT_WIN10
        #define _WIN32_WINNT 0x0A00
        #endif
    #elif _WIN32_WINNT_NT4
        #ifdef _WIN32_WINNT_NT4
        #define _WIN32_WINNT 0x0400
        #endif
    #elif _WIN32_WINNT_WIN2K
        #ifdef _WIN32_WINNT_WIN2K
        #define _WIN32_WINNT 0x0500
        #endif
    #elif _WIN32_WINNT_WINXP
        #ifdef _WIN32_WINNT_WINXP
        #define _WIN32_WINNT 0x0501
        #endif
    #elif _WIN32_WINNT_WS03
        #ifdef _WIN32_WINNT_WS03
        #define _WIN32_WINNT 0x0502
        #endif
    #elif _WIN32_WINNT_WIN6
        #ifdef _WIN32_WINNT_WIN6
        #define _WIN32_WINNT 0x0600
        #endif
    #elif _WIN32_WINNT_VISTA
        #ifdef _WIN32_WINNT_VISTA
        #define _WIN32_WINNT 0x0600
        #endif
    #elif _WIN32_WINNT_WS08
        #ifdef _WIN32_WINNT_WS08
        #define _WIN32_WINNT 0x0600
        #endif
    #elif _WIN32_WINNT_LONGHORN
        #ifdef _WIN32_WINNT_LONGHORN
        #define _WIN32_WINNT 0x0600
        #endif
    #elif _WIN32_WINNT_WIN7
        #ifdef _WIN32_WINNT_WIN7
        #define _WIN32_WINNT 0x0601
        #endif
    #elif _WIN32_WINNT_WIN8
        #ifdef _WIN32_WINNT_WIN8
        #define _WIN32_WINNT 0x0602
        #endif
    #elif _WIN32_WINNT_WINBLUE
        #ifdef _WIN32_WINNT_WINBLUE
        #define _WIN32_WINNT 0x0603
        #endif
    #else
        #ifdef _WIN32_WINNT_WINTHRESHOLD
        #define _WIN32_WINNT 0x0A00
        #endif
    #endif
    inline static void(*WinSockV)(int) = [](int i) mutable
    { //WinSockV(_WIN32_WINNT);
        std::cout << "OS WinSock -V : (" << typeid(i).name() << ") : " << i << " : ";

        OSVERSIONINFOEX info;
        ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
        info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
        GetVersionEx((LPOSVERSIONINFO)&info);

        printf("WINDOWS %u.%u\n", info.dwMajorVersion, info.dwMinorVersion); 
    };
#else
    inline static void(*WinSockV)(int) = [](int i) mutable
    { //WinSockV(_WIN32_WINNT);
        std::cout << "OS WinSock -V : (" << typeid(i).name() << ") : " << i << "  not defined : ";

        OSVERSIONINFOEX info;
        ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
        info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
        GetVersionEx((LPOSVERSIONINFO)&info);

        printf("WINDOWS %u.%u\n", info.dwMajorVersion, info.dwMinorVersion);
    };
#endif

template <class TYPE> struct ThrDVec{
	TYPE vec_x;
	TYPE vec_y;
	TYPE vec_z;
	ThrDVec(						 ) : vec_x(0 ), vec_y(0 ), vec_z(0 ) {}
	ThrDVec(TYPE _x					 ) : vec_x(_x), vec_y(0 ), vec_z(0 ) {}
	ThrDVec(TYPE _x, TYPE _y		 ) : vec_x(_x), vec_y(_y), vec_z(0 ) {}
	ThrDVec(TYPE _x, TYPE _y, TYPE _z) : vec_x(_x), vec_y(_y), vec_z(_z) {}
	ThrDVec operator+  (const ThrDVec& obj) {return ThrDVec(this->vec_x + obj.vec_x, this->vec_y + obj.vec_y, this->vec_z + obj.vec_z);}
	ThrDVec operator-  (const ThrDVec& obj) {this->vec_x - obj.vec_x;this->vec_y - obj.vec_y;this->vec_z - obj.vec_z;return *this;}
	ThrDVec operator*  (const ThrDVec& obj) {this->vec_x * obj.vec_x;this->vec_y * obj.vec_y;this->vec_z * obj.vec_z;return *this;}
	ThrDVec operator/  (const ThrDVec& obj) {this->vec_x / obj.vec_x;this->vec_y / obj.vec_y;this->vec_z / obj.vec_z;return *this;}
	ThrDVec& operator= (const ThrDVec& obj) = default;
	ThrDVec& operator+=(const ThrDVec& obj) const {this->vec_x += obj.vec_x;this->vec_y += obj.vec_y;this->vec_z += obj.vec_z;return *this;}
	ThrDVec& operator-=(const ThrDVec& obj) const {this->vec_x -= obj.vec_x;this->vec_y -= obj.vec_y;this->vec_z -= obj.vec_z;return *this;}
	ThrDVec& operator*=(const ThrDVec& obj) const {this->vec_x *= obj.vec_x;this->vec_y *= obj.vec_y;this->vec_z *= obj.vec_z;return *this;}
	ThrDVec& operator/=(const ThrDVec& obj) const {this->vec_x /= obj.vec_x;this->vec_y /= obj.vec_y;this->vec_z /= obj.vec_z;return *this;}
	bool operator ==   (const ThrDVec& obj) const {return (this->vec_x==obj.vec_x && this->vec_y==obj.vec_y && this->vec_z==obj.vec_z	 );}
	bool operator !=   (const ThrDVec& obj) const {return (this->vec_x!=obj.vec_x && this->vec_y!=obj.vec_y && this->vec_z!=obj.vec_z	 );}
	bool operator <=   (const ThrDVec& obj) const {return (this->vec_x<=obj.vec_x && this->vec_y<=obj.vec_y && this->vec_z<=obj.vec_z	 );}
	bool operator >=   (const ThrDVec& obj) const {return (this->vec_x>=obj.vec_x && this->vec_y>=obj.vec_y && this->vec_z>=obj.vec_z	 );}
	bool operator <    (const ThrDVec& obj) const {return (this->vec_x<obj.vec_x  && this->vec_y<obj.vec_y  && this->vec_z<obj.vec_z 	 );}
	bool operator >    (const ThrDVec& obj) const {return (this->vec_x>obj.vec_x  && this->vec_y>obj.vec_y  && this->vec_z>obj.vec_z 	 );}

	virtual int Aver(){int t= this->vec_z==0? 2: 3; return (this->vec_x + this->vec_y + this->vec_z)/t;										   			   }
	const std::string str() const {return "(" + std::to_string(this->vec_x) + "|" + std::to_string(this->vec_y) + "|" + std::to_string(this->vec_z) + ")"; }
	const std::vector<TYPE> store() const {return {this->vec_x, this->vec_y, this->vec_z};																   }
	
	friend std::ostream& operator<<(std::ostream& io, const ThrDVec& obj) { io << obj.str(); return io; 								   				   }
};

enum v{COORD_X, COORD_Y, COORD_Z, SIZE_VECTOR};

struct file{
    //some resources for FILE and the use of it ---- >>>>>
    //https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fopen-s-wfopen-s?view=msvc-170
    //https://cplusplus.com/reference/cstdio/fwrite/
    //https://cplusplus.com/reference/cstdio/fread/
	std::fstream fin;
	std::fstream fout;
    const char * copy;
    const char * paste;
    std::string * files;
    char * DataBuffer;
    file(                                       ) {}
    file(const char * _paste                    ) : paste(_paste)
    {
        fout.open(paste, std::ios::app); fout.close();
        fout.open(paste, std::ios::in | std::ios::out | std::ios::binary);
        if(!fout.is_open()) std::cout << paste << ": couldn't open" << std::endl;
    }
    file(const char * _copy, const char * _paste) : copy(_copy), paste(_paste)
    {
        fout.open(paste, std::ios::app); fout.close();
        fin.open(copy, std::ios::in | std::ios::out | std::ios::binary);
        if(!fin.is_open()) std::cout << copy << ": couldn't open" << std::endl;
        fout.open(paste, std::ios::in | std::ios::out | std::ios::binary);
        if(!fout.is_open()) std::cout << paste << ": couldn't open" << std::endl;
    }
    ~file(){fin.close(); fout.close();}

    inline void GetFileNames(const char * _copy, const char * _paste) { this->copy=_copy; this->paste=_paste;                          }
    inline void open        (FILE *fr, FILE *fw                     ) { fopen_s(&fr, this->copy, "rb");fopen_s(&fw, this->paste, "wb");}
	inline int  size        (                                       ) { fin.seekg(0, std::ios::end); return fin.tellg();               }
    inline int  fsize       (FILE *f                                ) { fseek(f, 0, SEEK_END);return ftell(f); rewind(f);              }
    
    inline void stack_copy(){////////////////////////////////////////////////////////////////////////////////
        std::cout << size() << ": " << std::endl << std::endl;
	    std::cout << "An already existing file will be overwritten, press ENTER to continue" << std::endl;
	    std::cin.get();

        char buffer;
	    int  percent = 0;

	    for(int i=0; i<=size(); ++i){
		    fin.seekg (i);
		    fin.read  (&buffer, sizeof(char));
		    fout.seekp(i);
		    fout.write(&buffer, sizeof(char));

		    if(i%(size()/100)==0){
			    std::cout << "-> copying[" << percent << "%]\n";
			    ++percent;
		    }
	    }

	    std::cout << "\ncopy process finished! press ESC to close..." << std::endl;

	    while(1){ if(GetAsyncKeyState(VK_ESCAPE & 0x1B)) break; }
    }
    inline void heap_copy(FILE *fr, FILE *fw){//////////////////////////////////////////////////////////////////////////////
	    std::cout << "An already existing file will be overwritten, press ENTER to continue" << std::endl;
	    std::cin.get();

        fopen_s(&fr, this->copy, "rb");
        fopen_s(&fw, this->paste, "wb");

        fseek(fr, 0, SEEK_END);
        size_t size = ftell(fr);
        rewind(fr);

	    char * buffer = new char[size];
	    fread(buffer, sizeof(char), size, fr);
	    fseek(fw, 0, SEEK_SET);
	    fwrite(buffer, sizeof(char), size, fw);

        std::cout << "\ncopy process finished! press ESC to close..." << std::endl;
	    while(1){ if(GetAsyncKeyState(VK_ESCAPE & 0x1B)) break; }

        fclose(fr); fclose(fw);
	    delete[] buffer;
    }



};

struct sockserv{};

class GetTexture{

    private:

    int IMG_Width;
    int IMG_Height;

    SDL_Texture * cTexture;

    public:

    struct sGet_Time{
        private:

        std::chrono::time_point<std::chrono::high_resolution_clock> nFirst;
        std::chrono::time_point<std::chrono::high_resolution_clock> nLast;
        std::chrono::duration<float> dDuration;

        public:

        sGet_Time() : nFirst(std::chrono::high_resolution_clock::now())                                                       {}
        ~sGet_Time() {nLast = std::chrono::high_resolution_clock::now(); dDuration = nLast - nFirst; printf("%f\n", dDuration);}
        void reset() {this->nFirst = std::chrono::high_resolution_clock::now();                                                }
    };


    GetTexture();
    ~GetTexture();

    void free();
    void LoadTexture(const char * PTH);
    void render(int x, int y, SDL_Rect * clip);
    void LOADIMG();

    int GetWidth();
    int GetHeight();
};

#endif
