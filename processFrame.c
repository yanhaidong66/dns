#include"head.h"
//ȫ�ֱ���
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
void getQr(unsigned char* frame, unsigned char* qr) {
	unsigned char c = frame[2];
	*qr = (c>>7)&0b1;
	printf("qr:" );
	printHex(*qr);
	printf("\n");
}

void getOpcode(char* frame,unsigned char* opcode) {
	char c=frame[2];
	*opcode = (c&01111000)>>3;
	printf("opcode:");
	printHex(*opcode);
	printf("\n");

}
//����λ
void getAa(char* frame, unsigned char* aa) {
	unsigned char c = frame[2];
	*aa = (c & 0b00000100)>>2;
	printf("aa:");
	printHex(*aa);
	printf("\n");

}
//����λ
void getTc(char* frame, unsigned char* tc) {
	unsigned char c = frame[2];
	*tc = (c & 0b00000010) >> 1;
	printf("tc:");
	printHex(*tc);
	printf("\n");
}
//�ڰ�λ
void getRd(char* frame, unsigned char* rd) {
	unsigned char c = frame[2];
	*rd = (c & 0b1);
	printf("rd:");
	printHex(*rd);
	printf("\n");
}
//�ھ�λ
void getRa(char* frame, unsigned char* ra) {
	unsigned char c = frame[3];
	*ra = (c & 0b10000000) >> 7;
	printf("ra:");
	printHex(*ra);
	printf("\n");
}
//ʮ��λ��ʮ��λ
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
	char* ptr=&frame[13];//ָ��frame��ָ�룬������ȡ����
	
	for (int query_count = 0; query_count < queriesCount; query_count++) {
		
		int k = 0;//q�е�һ��domain���ַ�λ��
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
int makeFrame(char ip[], char returnFrame[]) {

}




//�������frame��charΪ����8λ
int processFrame(char frame[], int frameSize, char returnFrame[]) {
	requestionFrame* rf=(requestionFrame*)calloc(sizeof(requestionFrame),1);
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