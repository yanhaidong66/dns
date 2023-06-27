#include"head.h"

void getDomain(char frame[], char domain[]) {
	char* ptr = &frame[13];//指向frame的指针，挨个读取内容

	int k = 0;//q中的一个domain的字符位置
	for (; (*ptr) != '\0'; ptr++) {

		if ((*ptr) < 30) {
			domain[k] = '.';
			k++;
		}
		else {
			domain[k] = *ptr;
			k++;
		}
	}
	printf("domain:%s\n",domain);

}


void getId(char* frame, unsigned char* id) {
	//printf("\nid:");
	for (int i = 0; i < 2; i++) {
		id[i] = frame[i];
		//printBinary(id[i]);
	}
	//printf("\n");
	
}
//0是查询dns报文，1是回应dns报文
void getQr(unsigned char* frame, unsigned char* qr) {
	unsigned char c = frame[2];
	*qr = (c>>7)&0b1;
	//printf("qr:" );
	//printBinary(*qr);
	//printf("\n");
}

void getOpcode(char* frame,unsigned char* opcode) {
	char c=frame[2];
	*opcode = (c&01111000)>>3;
	//printf("opcode:");
	//printBinary(*opcode);
	//printf("\n");

}
//
void getAa(char* frame, unsigned char* aa) {
	unsigned char c = frame[2];
	*aa = (c & 0b00000100)>>2;
	//printf("aa:");
	//printBinary(*aa);
	//printf("\n");

}
//tc：请求报文中的，udp可否截断
void getTc(char* frame, unsigned char* tc) {
	unsigned char c = frame[2];
	*tc = (c & 0b00000010) >> 1;
	//printf("tc:");
	//printBinary(*tc);
	//printf("\n");
}
//rd：是否递归请求
void getRd(char* frame, unsigned char* rd) {
	unsigned char c = frame[2];
	*rd = (c & 0b1);
	//printf("rd:");
	//printBinary(*rd);
	//printf("\n");
}
//ra：服务器回应，是否可用递归查询
void getRa(char* frame, unsigned char* ra) {
	unsigned char c = frame[3];
	*ra = (c & 0b10000000) >> 7;
	//printf("ra:");
	//printBinary(*ra);
	//printf("\n");
}
//十二位到十六位
void getRcode(char* frame, unsigned char* rcode) {
	unsigned char c = frame[3];
	*rcode = c&0b1111;
	//printf("rcode:");
	//printBinary(*rcode);
	//printf("\n");
}

void getQueryCount(char* frame,int* questionCount) {
	unsigned char c[2];
	c[0] = frame[4];
	c[1] = frame[5];

	*questionCount = c[0] * 256+ c[1] ;
	//printf("questionCount:%d\n", *questionCount);
}
void getAnswerCount(char* frame,int* answerCount) {
	unsigned char c[2];
	c[0] = frame[6];
	c[1] = frame[7];

	*answerCount = c[0] * 256 + c[1];
	//printf("questionCount:%d\n", *answerCount);
}
void getAuthorityCount(char* frame,int* authorityCount) {
	unsigned char c[2];
	c[0] = frame[8];
	c[1] = frame[9];

	*authorityCount = c[0] * 256 + c[1];
	//printf("questionCount:%d\n", *authorityCount);
}
void getAdditionCount(char* frame, int* additionCount) {
	unsigned char c[2];
	c[0] = frame[10];
	c[1] = frame[11];

	*additionCount = c[0] * 256 + c[1];
	//printf("questionCount:%d\n", *additionCount);
}
void getQueries(char* frame,int frameSize,int queriesCount,query* q) {
	char* ptr=&frame[13];//指向frame的指针，挨个读取内容
	

		int k = 0;//q中的一个domain的字符位置
		//printf("\nquery:\n");
		for (;(*ptr)!='\0'; ptr++) {
			
			if ((*ptr) < 30) {
			q->domain[k] = '.';
			k++;
			}
			else {
				q->domain[k] = *ptr;
				k++;
			}
		}
		ptr++;
		q->type = (*ptr) * 256 + *(++ptr);
		ptr++;
		q->query_class = (*ptr) * 256 + *(++ptr);
		//printf("type:%d\n",q->type);
		//printf("class:%d\n",q->query_class);
		//printf("%s\n", q->domain);
		
		
	
}



//制作回应帧，要求改变flags位（qr：改为0，回应报文,ra：改为1，dns服务器可用递归）和answer rrs位为1.query部分不需要改变，在query最后添加answer rrs
int makeRespnseFrame(responseFrame* rpf,requestionFrame rf) {
	printf("responseFrame:\n");
	frameCopy(rpf->frame, rf.frame, rf.sizeOfFrame);
	//将qr改为1，标志为回应报文
	char qr = rpf->frame[2];
	qr = qr | 0b10000000;
	rpf->frame[2] = qr;
	//printf("qr:");
	//printBinary(qr);


	//将ra改为1，服务器可用递归查询
	char ra = rpf->frame[3];
	ra = ra | 0b10000000;
	rpf->frame[3] = ra;
	//printf("\nra:");
	//printBinary(ra);


	//将answer rrs数设置为1
	char answerCount= rpf->frame[7];
	answerCount = 1;
	rpf->frame[7] = answerCount;
	//printf("\nanswerCount:");
	//printBinary(answerCount);

	//制作answer rrs部分
	char answer[32];
	//设置response回答的域名，是一个指针，固定指向query的域名位置
	answer[0] = 0xc0;
	answer[1] = 0x0c;
	//设置rrs的type
	answer[2]=0;
	answer[3]=1;
	//设置rrs的class
	answer[4]=0;
	answer[5]=1;
	//设置time to live，回答在客户电脑中存放多长时间
	answer[6]=1;
	answer[7]=1;
	answer[8]=1;
	answer[9]=1;
	//rrs内容的字节数（也就是ip地址的长度，为4）
	answer[10]=0;
	answer[11]=4;
	//设置ip地址,将字符串ip转换为4个每个8位都用来存储的char
	char ip[MAX_LEN_IP] = { 0 };
	strCopy(ip, rf.ip);
	inet_pton(AF_INET, ip, &answer[12]);
	//printf("\nquery:");
	//printCharToBinary(rf.frame, rf.sizeOfFrame);
	//printf("\nanswer:");
	//printCharToBinary(answer,16);
	
	strCopy(rpf->domain, rf.domain);
	strCopy(rpf->ip, rf.ip);

	//将answer rrs添加到query末尾
	frameCopy(&rpf->frame[rf.sizeOfFrame], answer, 16);




	rpf->sizeOfFrame = rf.sizeOfFrame+16;

	//printf("responseFrame:\n");
	//printCharToBinary(rpf->frame, rpf->sizeOfFrame);


	return 1;
}




//传入的是frame的char为流的8位
 int processFrame(char frame[], int frameSize,responseFrame* rpf,requestionFrame* rf) {
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
	getQueryCount(frame,&rf->questionCount);
	getAnswerCount(frame, &rf->answerCount);
	getAuthorityCount(frame, &rf->authorityCount);
	getAdditionCount(frame, &rf->additionCount);
	getQueries(frame,frameSize, rf->questionCount, &rf->queries);

	//如果查找到ip
	if (searchIp(rf->domain, rf->ip)==1) {
		makeRespnseFrame(rpf,*rf);
		return 1;
	}
	//查不到ip
	else {
		strCopy(rpf->domain, rf->domain);
		strCopy(rpf->ip, rf->ip);
		return 0;
	}

}

 int getIpAndDomainFromFrame(responseFrame* rpf, int sizeOfFrame) {
	 int ip[4] = { 0 }; 
	 int len = 0;
	 ip[0] = (int)rpf->frame[44];
	 ip[1] = (int)rpf->frame[45];
	 ip[2] = (int)rpf->frame[46];
	 ip[3] = (int)rpf->frame[47];
	 len += intToCharArray(rpf->ip, ip[0]);
	 rpf->ip[len] = '.';
	 len++;
	 len += intToCharArray((rpf->ip)+len, ip[1]);
	 rpf->ip[len] = '.';
	 len++;
	 len += intToCharArray((rpf->ip) + len, ip[2]);
	 rpf->ip[len] = '.';
	 len++;
	 len += intToCharArray((rpf->ip) + len, ip[3]);

	 char* ptr = & (rpf->frame[13]);//指向frame的指针，挨个读取内容


	 int k = 0;//q中的一个domain的字符位置
	 for (; (*ptr) != '\0'; ptr++) {

		 if ((*ptr) < 30) {
			 rpf->domain[k] = '.';
			 k++;
		 }
		 else {
			 rpf->domain[k] = *ptr;
			 k++;
		 }
	 }
	 printf(":::::::::%s", rpf->domain);

	 return 1;

 }