##/*******************************************
##** (C) Devin Taietta 
##** Informazioni su com
##** Necessari:
##** Ubuntu: 
##** Arch:
##*********************************************/
##!bash
echo -e  "\n\n\t    [FASE 1: ELIMINO VECCHI FILE]"
rm a.out mpg123.o aosender.o AudioPlayer
echo -e  "\n\n\t    [FASE 2: COMPILO FILE IN C]"
gcc -c -g "Process/mpg123.c" "Output/aosender.c" #"Process/sampleConversion.c"
echo -e  "\n\n\t    [FASE 3: COMPILO FILE IN C++]"
g++ -g "aosender.o" "Input/usbData.cpp" "Input/Socket/Server.cpp" "Process/dataManagerHub.cpp" "Process/util.cpp" "mpg123.o" "Process/Riproduttore.cpp" "main_cli.cpp" -lao -lmpg123  -lavcodec -lavformat -std=c++0x -o AudioPlayer #"Process/ffmpeg.cpp"
echo -e  "\n\n\t    [FASE 4: RENDO ESEGUIBILE L'OUTPUT]"
chmod 775 AudioPlayer
##echo -e  "\n\n\t    [FASE 5: ESEGUO IL PROGRAMMA]"
./AudioPlayer "/media/"
##./a.out "/home/devin/Documenti/Console/WebManager/uploadedFiles/"
echo -e "\n\n\t    [FASE 5: ESEGUI IL PROGRAMMA - MODALITA DEBUG]"
#gdb -tui AudioPlayer
#echo -e  "\n\n\t    [FASE 6: ELIMINO IL PROGRAMMA E I FILE]"
#rm AudioPlayer mpg123.o aosender.o
