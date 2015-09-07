///@file
// Devin Taietta
// usbData.cpp -- Gestione dell'archivio delle canzoni e ottenimento informazioni sui file
//Dynamic Linked
#include <iostream>
#include <string>
#include <vector>
#include <errno.h>	//Managing Error
//Static Linked
#include "usbData.h"
#include "/usr/include/taglib/fileref.h"
#include "/usr/include/taglib/tag.h" //Per trovare i tag ID3 delle canzoni
//Only Linux - Browse directories
#include <dirent.h> //Access to Linux Directory
#include <sys/stat.h> //Information about attribs of files
using namespace std;

usbData::usbData(std::string baseDir,bool recursive)
{
	usbData::riempiArchivio(baseDir,recursive,*this);
	if (elementi.size()<=0) {
			std::cout<<"Nessuna canzone trovata al percorso indicato!";;
			sleep(3);
			usbData::riempiArchivio(baseDir,recursive,*this); //Media
	}
	puntatore=0;
}
void usbData::setPuntatore(int posizione){puntatore=posizione;}
int usbData::getPuntatore() {return puntatore;}

bool usbData::isAudio (std::string percorso,bool onlymp3) {
	std::string validformat[6] = {"MP3","mp3","WAW","waw","FLAC","flac"};
	int imax;
	if (onlymp3) {
		imax=2;
	} else {

		imax=6;
	}
	for (int i=0;i<imax;i++)
		{
			if (percorso[percorso.length()-3]==validformat[i][0]&&
					percorso[percorso.length()-2]==validformat[i][1]&&
					percorso[percorso.length()-1]==validformat[i][2])
					{
						return true;
					}
		}
	return false;
}

bool usbData::isDir(string dir)
{
	struct stat fileInfo;
	stat(dir.c_str(), &fileInfo);
	if (S_ISDIR(fileInfo.st_mode))
	{
		return true;
	}else{
		return false;
	}
}

void usbData::riempiArchivio(string baseDir, bool recursive, usbData &arc)
{
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(baseDir.c_str())) == NULL) {
		//Genera errore apertura cartella!
		return;
	} else {
		while ((dirp = readdir(dp)) != NULL) {
			if (dirp->d_name != string(".") && dirp->d_name != string ("..")) {
				if (usbData::isDir(baseDir + dirp->d_name) == true && recursive==true) {
					usbData::riempiArchivio(baseDir + dirp->d_name + "/",true,arc);
				} else {
					if (usbData::isAudio(dirp->d_name,false)) {
							arc.elementi.push_back((string)(baseDir+dirp->d_name));
					}
				}
			}
		}
	}
}
