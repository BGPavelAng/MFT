
;/////bgpavelang.github.io//////
;///Gracias por darle credito a mi trabajo/////
;//////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#pragma pack(push, 1)
typedef struct _BIOS_PARAMETERS_BLOCK
{
	USHORT    BytesPerSector;
	UCHAR     SectorsPerCluster;
	UCHAR     Unused0[7];
	UCHAR     MediaId;
	UCHAR     Unused1[2];
	USHORT    SectorsPerTrack;
	USHORT    Heads;
	UCHAR     Unused2[4];
	UCHAR     Unused3[4];
} BIOS_PARAMETERS_BLOCK, *PBIOS_PARAMETERS_BLOCK;

typedef struct _EXTENDED_BIOS_PARAMETERS_BLOCK
{
	USHORT    Unknown[2];
	ULONGLONG SectorCount;
	ULONGLONG MftLocation;
	ULONGLONG MftMirrLocation;
	CHAR      ClustersPerMftRecord;
	UCHAR     Unused4[3];
	CHAR      ClustersPerIndexRecord;
	UCHAR     Unused5[3];
	ULONGLONG SerialNumber;
	UCHAR     Checksum[4];
} EXTENDED_BIOS_PARAMETERS_BLOCK, *PEXTENDED_BIOS_PARAMETERS_BLOCK;

typedef struct _BOOT_SECTOR
{
	UCHAR     Jump[3];
	UCHAR     OEMID[8];
	BIOS_PARAMETERS_BLOCK BPB;
	EXTENDED_BIOS_PARAMETERS_BLOCK EBPB;
	UCHAR     BootStrap[426];
	USHORT    EndSector;
} BOOT_SECTOR, *PBOOT_SECTOR;
#pragma pack(pop)

int main(int args, char*argv[])
{

	CHAR SzSymDrive[40] = "\\\\.\\C:";
	HANDLE hDrive;
	BYTE DriveContent[1024];
	BYTE ManContent[1024], NamSz[200], NamLz[200];
	char FIL[4];
	DWORD BytesRead;
	PBOOT_SECTOR lpBootSector;
	LARGE_INTEGER MFTLcl;
	int n = 0, m = 0, pos, j= 0, sum = 0, k = 0;

	hDrive = CreateFileA(SzSymDrive, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hDrive == INVALID_HANDLE_VALUE)
	{
		return;
	}

	if ((!ReadFile(hDrive, DriveContent, sizeof(DriveContent), &BytesRead, NULL)) || (BytesRead != sizeof(DriveContent)))
	{
		goto clhandle;
	}

	lpBootSector = (PBOOT_SECTOR)DriveContent;
	MFTLcl.QuadPart = lpBootSector->BPB.BytesPerSector * lpBootSector->BPB.SectorsPerCluster * lpBootSector->EBPB.MftLocation;

	if (SetFilePointer(hDrive, MFTLcl.LowPart, &MFTLcl.HighPart, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		goto clhandle;
	}

	while (1) {
		if ((!ReadFile(hDrive, DriveContent, sizeof(DriveContent), &BytesRead, NULL)) || (BytesRead != sizeof(DriveContent)))
		{
			goto clhandle;
		}
		
		

		for (n = 0; n < sizeof(DriveContent); n++) { //Analiza todo el array de DriveContent

			ManContent[n] = DriveContent[n]; //Mete en otro array los datos para manipularlos sin modificar nada en DriveContent
			for (m = 0; m < 4; m++) {
				FIL[m] = ManContent[m]; //Para verificar si es FILE el archivo
			}
		}
			if (strcmp(FIL, "FILE") == 0 && ManContent[22] == 0) {

				if (ManContent[152] == 48) { //para llegar a 0x30 donde se encuentran los nombres

					pos = ManContent[156];

					for (j = 0; j <= pos; j++) {

						NamSz[j] = ManContent[152 + j];

					}

					sum = NamSz[88] * 2;

					for (k = 0; k < sum; ++k) {
						
						if (NamSz[90 + k] != 0) {
							printf("%c", NamSz[90 + k]);
						}
						if (k > sum) {
							printf("\t\t");

					}

				}

				if (ManContent[272] == 48) { //para llegar a 0x30 de Longbane donde se encuentran los nombres

					pos = ManContent[276];

					for (j = 0; j <= pos; j++) {

						NamLz[j] = ManContent[272 + j];

					}

					sum = NamLz[88] * 2;

					for (k = 0; k < sum; ++k) {

						if (NamLz[90 + k] != 0) {
							printf("%c", NamLz[90 + k]);
						}
						}

					}

				}

				printf("\n\n");
				

			}

		
		fflush(stdout);

	}

		getchar();
clhandle:
	CloseHandle(hDrive);

}

