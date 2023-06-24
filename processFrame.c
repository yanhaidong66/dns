#include"head.h"
//全局变量
extern database db;

void getDomain(char frame[], char domain[]) {
	
}

void getIp(char domain[], char ip[]) {

}

void getId(char* frame, unsigned char* id) {
	printf("\nid:");
	for (int i = 0; i < 2; i++) {
		id[i] = frame[i];
		printHex(id[i]);
	}
	printf("\n");
	
}
void getQr(char* frame, unsigned char* qr) {
	char c = frame[2];
	printHex(c);
	char x = c >> 7;
	*qr = (c>>7)&0b1;
	printf("qr:" );
	printHex(*qr);
	printf("\n");
	
}
//将帧中的opcode存储在传入变量opcode的第四位中
void getOpcode(char* frame,unsigned char* opcode) {
	char c=frame[2];
	*opcode = (c&01111000)>>3;
	printf("opcode:");
	printHex(*opcode);
	printf("\n");

}
//第六位
void getAa(char* frame, unsigned char* aa) {
	unsigned char c = frame[2];
	*aa = (c & 0b00000100)>>2;
	printf("aa:");
	printHex(*aa);
	printf("\n");

}
//第七位
void getTc(char* frame, unsigned char* tc) {
	unsigned char c = frame[2];
	*tc = (c & 0b00000010) >> 1;
	printf("tc:");
	printHex(*tc);
	printf("\n");
}
//第八位
void getRd(char* frame, unsigned char* rd) {
	unsigned char c = frame[2];
	*rd = (c & 0b1);
	printf("rd:");
	printHex(*rd);
	printf("\n");
}
//第九位
void getRa(char* frame, unsigned char* ra) {
	unsigned char c = frame[3];
	*ra = (c & 0b10000000) >> 7;
	printf("ra:");
	printHex(*ra);
	printf("\n");
}
//十二位到十六位
void getRcode(char* frame, unsigned char* rcode) {
	unsigned char c = frame[3];
	*rcode = c&0b1111;
	printf("rcode:");
	printHex(*rcode);
	printf("\n");
}

void getQueryCount(char* frame,int* questionCount) {
	unsigned char c[2];
	c[0] = frame[4];
	c[1] = frame[5];

	*questionCount = c[0] * 256+ c[1] ;
	printf("questionCount:%d\n", *questionCount);
}
void getAnswerCount(char* frame,int* answerCount) {
	unsigned char c[2];
	c[0] = frame[6];
	c[1] = frame[7];

	*answerCount = c[0] * 256 + c[1];
	printf("questionCount:%d\n", *answerCount);
}
void getAuthorityCount(char* frame,int* authorityCount) {
	unsigned char c[2];
	c[0] = frame[8];
	c[1] = frame[9];

	*authorityCount = c[0] * 256 + c[1];
	printf("questionCount:%d\n", *authorityCount);
}
void getAdditionCount(char* frame, int* additionCount) {
	unsigned char c[2];
	c[0] = frame[10];
	c[1] = frame[11];

	*additionCount = c[0] * 256 + c[1];
	printf("questionCount:%d\n", *additionCount);
}
void getQueries(char* frame,int frameSize,int queriesCount,query* q) {
	char* ptr=&frame[12];
	printf("query:");
	for (int j = 0;j<(frameSize-12); j++) {
		if (ptr[j] < 30)
			printf("%d", ptr[j]);
		else
			printf("%c", ptr[j]);
	}
	for (int i = 0; i < queriesCount; i++) {
		
		
	}
}
int makeFrame(char ip[], char returnFrame[]) {

}




//传入的是frame的char为流的8位
int processFrame(char frame[], int frameSize, char returnFrame[]) {
	requestionFrame* rf=(requestionFrame*)malloc(sizeof(requestionFrame));
	getId(frame, rf->id);
	getQr(frame, &rf->qr);
	getOpcode(frame, &rf->opcode);
	getAa(frame, &rf->aa);
	getTc(frame, &rf->tc);
	getRd(frame, &rf->rd);
	getRa(frame, &rf->ra);
	getRcode(frame, &rf->rcode);
	getDomain(frame,rf->domain);
	getIp(frame, rf->ip);
	getQueryCount(frame,&rf->questionCount);
	getAnswerCount(frame, &rf->answerCount);
	getAuthorityCount(frame, &rf->authorityCount);
	getAdditionCount(frame, &rf->additionCount);
	getQueries(frame,frameSize, rf->questionCount, &rf->queries);
	

	
}