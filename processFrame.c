#include"head.h"
extern database db;

void getDomain(char frame[], char domain[]) {
	
}

void getIp(char domain[], char ip[]) {

}

void getId(char* frame, unsigned char* id) {
	printf("\nid:");
	for (int i = 0; i < 2; i++) {
		id[i] = frame[i];
		printBinary(id[i]);
	}
	printf("\n");
	
}
void getQr(unsigned char* frame, unsigned char* qr) {
	unsigned char c = frame[2];
	*qr = (c>>7)&0b1;
	printf("qr:" );
	printBinary(*qr);
	printf("\n");
}

void getOpcode(char* frame,unsigned char* opcode) {
	char c=frame[2];
	*opcode = (c&01111000)>>3;
	printf("opcode:");
	printBinary(*opcode);
	printf("\n");

}
//第六位
void getAa(char* frame, unsigned char* aa) {
	unsigned char c = frame[2];
	*aa = (c & 0b00000100)>>2;
	printf("aa:");
	printBinary(*aa);
	printf("\n");

}
//第七位
void getTc(char* frame, unsigned char* tc) {
	unsigned char c = frame[2];
	*tc = (c & 0b00000010) >> 1;
	printf("tc:");
	printBinary(*tc);
	printf("\n");
}
//第八位
void getRd(char* frame, unsigned char* rd) {
	unsigned char c = frame[2];
	*rd = (c & 0b1);
	printf("rd:");
	printBinary(*rd);
	printf("\n");
}
//第九位
void getRa(char* frame, unsigned char* ra) {
	unsigned char c = frame[3];
	*ra = (c & 0b10000000) >> 7;
	printf("ra:");
	printBinary(*ra);
	printf("\n");
}
//十二位到十六位
void getRcode(char* frame, unsigned char* rcode) {
	unsigned char c = frame[3];
	*rcode = c&0b1111;
	printf("rcode:");
	printBinary(*rcode);
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
	char* ptr=&frame[13];//指向frame的指针，挨个读取内容
	
	for (int query_count = 0; query_count < queriesCount; query_count++) {
		
		int k = 0;//q中的一个domain的字符位置
		printf("query(%d):\n",query_count);
		for (;(*ptr)!='\0'; ptr++) {
			
			if ((*ptr) < 30) {
			q->domain[query_count][k] = '.';
			k++;
			}
			else {
				q->domain[query_count][k] = *ptr;
				k++;
			}
		}
		ptr++;
		q->type = (*ptr) * 256 + *(++ptr);
		ptr++;
		q->query_class = (*ptr) * 256 + *(++ptr);
		printf("type:%d\n",q->type);
		printf("class:%d\n",q->query_class);
		printf("%s\n", q->domain[query_count]);
		
		
	}
}




int makeRespnseFrame(responseFrame* rpf,requestionFrame rf) {
	frameCopy(rpf->frame, rf.frame, rf.sizeOfFrame);
	rpf->sizeOfFrame = rf.sizeOfFrame;





	return 1;
}




//传入的是frame的char为流的8位
int processFrame(char frame[], int frameSize, char returnFrame[]) {
	requestionFrame* rf=(requestionFrame*)calloc(sizeof(requestionFrame),1);
	responseFrame* rpf = (responseFrame*)calloc(sizeof(responseFrame), 1);
	frameCopy(rf->frame, frame, frameSize);
	rf->sizeOfFrame = frameSize;
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
	makeRespnseFrame(rpf,*rf);
	printCharToBinary(rpf->frame,rpf->sizeOfFrame);
	printf("frameSize::::::%d", rpf->sizeOfFrame);

	
}