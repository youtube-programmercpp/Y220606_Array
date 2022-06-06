#include <Windows.h>
void Test(int a[])
{
	//a[-1] = 0;
	a[0] = 0;
	a[1023] = 0;
	int* p = &a[1024];
	p[0] = 0;
	//a[1024] = 0;
}
int main()
{
	SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);

	const LPVOID lpAddress = VirtualAlloc
	( /*_In_opt_ LPVOID lpAddress       */NULL
	, /*_In_     SIZE_T dwSize          */3 * (SIZE_T)system_info.dwPageSize
	, /*_In_     DWORD  flAllocationType*/MEM_COMMIT
	, /*_In_     DWORD  flProtect       */PAGE_READWRITE
	);
	if (lpAddress) {
		//先頭の 4096 バイトは読み書き禁止
		//続く 4096 バイトは読み書き自由
		//更に後続の 4096 バイトは読み書き禁止
		DWORD dwOldProtect;
		(void)VirtualProtect
		( /*_In_  LPVOID lpAddress     */lpAddress
		, /*_In_  SIZE_T dwSize        */system_info.dwPageSize
		, /*_In_  DWORD  flNewProtect  */PAGE_NOACCESS
		, /*_Out_ PDWORD lpflOldProtect*/&dwOldProtect
		);
		(void)VirtualProtect
		( /*_In_  LPVOID lpAddress     */&((LPSTR)lpAddress)[2 * (SIZE_T)system_info.dwPageSize]
		, /*_In_  SIZE_T dwSize        */system_info.dwPageSize
		, /*_In_  DWORD  flNewProtect  */PAGE_READONLY
		, /*_Out_ PDWORD lpflOldProtect*/&dwOldProtect
		);
		Test((int*) & ((LPSTR)lpAddress)[system_info.dwPageSize]);
		(void)VirtualFree
		( /*_Pre_notnull_
			_When_(dwFreeType == MEM_DECOMMIT, _Post_invalid_)
			_When_(dwFreeType == MEM_RELEASE, _Post_ptr_invalid_)
		           LPVOID lpAddress */lpAddress
		, /*_In_   SIZE_T dwSize    */0
		, /*_In_   DWORD  dwFreeType*/MEM_RELEASE
		);
	}


}
