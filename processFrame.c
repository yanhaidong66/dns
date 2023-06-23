#include"config.h"
#include<stdlib.h>
#include"util.h"
#include"struct.h"
void getDomain(char frame[], char domain[]) {
	
}

void getIp(char domain[], char ip[]) {

}

void getId(char* frame, unsigned char* id) {
	printf("\nid:");
	for (int i = 0; i < 4; i++) {
		id[i] = frame[i];
		printf("%x", id[i]);
	}
	printf("\n");
	
}
void getQr(char* frame, unsigned char* qr) {
	char c = frame[4];
	*qr = (c&0b1000)>>3;
	printf("qr:" );
	printHex(*qr);
	printf("\n");
	
}
void getOpcode(char* frame,unsigned char* opcode) {
	char c[2];
	c[0] = frame[4];
	c[1] = frame[5];
	*opcode = (c[0]&0b0111)<<1;
	*opcode += (c[1]&0b1000)>>3;
	printf("opcode:");
	printHex(*opcode);
	printf("\n");

}
//第六位
void getAa(char* frame, unsigned char* aa) {
	unsigned char c = frame[5];
	*aa = (c & 0b100)>>2;
	printf("aa:");
	printHex(*aa);
	printf("\n");

}
//第七位
void getTc(char* frame, unsigned char* tc) {
	unsigned char c = frame[5];
	*tc = (c & 0b10) >> 1;
	printf("tc:");
	printHex(*tc);
	printf("\n");
}
//第八位
void getRd(char* frame, unsigned char* rd) {
	unsigned char c = frame[5];
	*rd = (c & 0b1);
	printf("rd:");
	printHex(*rd);
	printf("\n");
}
//第九位
void getRa(char* frame, unsigned char* ra) {
	unsigned char c = frame[6];
	*ra = (c & 0b1000) >> 3;
	printf("ra:");
	printHex(*ra);
	printf("\n");
}
//十二位到十六位
void getRcode(char* frame, unsigned char* rcode) {
	unsigned char c = frame[7];
	*rcode = c;
	printf("rcode:");
	printHex(*rcode);
	printf("\n");
}

void getQueryCount(char* frame,int* questionCount) {
	unsigned char c[4];
	c[0] = frame[8];
	c[1] = frame[9];
	c[2] = frame[10];
	c[3] = frame[11];
	*questionCount = c[0] * 16 * 16 * 16 + c[1] * 16 * 16 + c[2] * 16 + c[3];
	printf("questionCount:%d\n", *questionCount);
}
void getAnswerCount(char* frame,int* answerCount) {
	unsigned char c[4];
	c[0] = frame[12];
	c[1] = frame[13];
	c[2] = frame[14];
	c[3] = frame[15];
	*answerCount = c[0] * 16 * 16 * 16 + c[1] * 16 * 16 + c[2] * 16 + c[3];
	printf("questionCount:%d\n", *answerCount);
}
void getAuthorityCount(char* frame,int* authorityCount) {
	unsigned char c[4];
	c[0] = frame[16];
	c[1] = frame[17];
	c[2] = frame[18];
	c[3] = frame[19];
	*authorityCount = c[0] * 16 * 16 * 16 + c[1] * 16 * 16 + c[2] * 16 + c[3];
	printf("questionCount:%d\n", *authorityCount);
}
void getAdditionCount(char* frame, int* additionCount) {
	unsigned char c[4];
	c[0] = frame[20];
	c[1] = frame[21];
	c[2] = frame[22];
	c[3] = frame[23];
	*additionCount = c[0] * 16 * 16 * 16 + c[1] * 16 * 16 + c[2] * 16 + c[3];
	printf("questionCount:%d\n", *additionCount);
}
void getQueries(char* frame,int frameSize,int queriesCount,query* q) {
	char* ptr=&frame[24];
	char* q_char[100] = { 0 };
	printf("query:");
	for (int j = 0;j<(frameSize-24)*2; j++) {
		q_char[j] += (*ptr) << 4;
		ptr++;
		q_char[j] += (*ptr);
		ptr++;
		if (q_char[j] < 30)
			printf("%d", q_char[j]);
		else
			printf("%c", q_char[j]);
	}
	for (int i = 0; i < queriesCount; i++) {
		
		
	}
}
int makeFrame(char ip[], char returnFrame[]) {

}




//传入的是char为4位转换位整数
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