#include"head.h"


void* ispServerPart() {
	char frame[MAX_FRAME_SIZE] = { 0 };
	responseFrame* rpf= (responseFrame*)calloc(sizeof(responseFrame), 1);//给用户的回应帧
	requestionFrame* rf = (requestionFrame*)calloc(sizeof(requestionFrame), 1);//用户发来的请求帧
				

	while (1) {
		struct sockaddr_in recvAddr;
		int recvAddrLen=0;
		rf->sizeOfFrame = recvfrom(socketWithIsp, rf->frame, sizeof(rf->frame), 0, (struct socketaddr*)&recvAddr, &recvAddrLen);
		if (rf->sizeOfFrame < 0) {
			perror("Error in recvfrom");
			continue;
		}
		rpf = processFrame(rf->frame, rf->sizeOfFrame);

		//将dns上级服务器的相应帧存入数据库
		addIpAndDomain(rf->domain, rf->ip);



		//id上锁
		pthread_mutex_lock(&mutex_id);
		//确定发送给哪个用户
		struct sockaddr_in converClientAddr;	//转发的客户对象的地址
		int clientId = 0;
		clientId = (rf->id[0] >> 4) * 16 * 16 * 16 + (rf->id[0] & 0b00001111) * 16 * 16 + (rf->id[1] >> 4) * 16 + (rf->id[1] & 0b00001111);
		printf("\nclient_myId:%d",clientId);
		
		//通过ispSocket向用户发送
		if (sendto(socketWithClient, rpf->frame, rpf->sizeOfFrame, 0, (const struct sockaddr*)&id[clientId].addr, clientAddrLen) < 0) {
			perror("Error in sendto");
			exit(EXIT_FAILURE);
		}
		pthread_mutex_unlock(&mutex_id);


	}
	
	free(rpf);


}