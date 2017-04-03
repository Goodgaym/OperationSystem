#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<process.h>
DWORD WINAPI ThreadFunction(void* arg);
int main(){
    HANDLE hThread;
    DWORD dwThreadID, dw;
    hThread = (HANDLE)_beginthreadex(NULL, 0
        (unsigned int(__stdcall*)(void*))ThreadFunction, NULL, 0, (unsigned*)&dwThereadID);
    if(hThread == 0){
        puts("_beginthreadex() error");
        exit(1);
    }
    printf("생성된 쓰레드 핸들 : %d\n", hThread);
    printf("생성된 쓰레드 ID : %d\n", dwThread);
    dw = WaitForSingleObject(hThread, 3000);
    if (dw == WAIT_FAILED){
        puts("쓰레드의 비정상적인 종료");
        exit(1);
    }
    else{
        pritnf("main 함수 종료. %s종료\n", (dw == WAIT_OBJECT_0)? "정상":"비정상");
    }
    return 0;
}
DWORD WINAPI ThreadFunction(void* arg){
    int i;
    for(i=0; i<5; i++){
        Sleep(500);
        printf("쓰레드 실행 중 %d \n", i);
    }
    return 0;
}